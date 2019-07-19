from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
from flask import jsonify

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite databases
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():

    # get current portfolio
    portfolio = db.execute("SELECT symbol, SUM(qty) qty, unit_price, AVG(unit_price) as average_price, (unit_price*qty) total FROM portfolio WHERE user_id = :user_id GROUP BY symbol", user_id = session["user_id"] )

    # it would be nice to have the current price, and compare with the price that it was bought
    # DONE, but it´s not working ok, cause it´s grouping, and bought prices are different..
    # so showing average aquisition prices

    current_price = []

    for item in portfolio:
        quote = lookup(item['symbol'])
        if quote:
            current_price.append({item['symbol'] : quote['price']})
        else:
            return "unable to get quote for "+item['symbol']

    return render_template("index.html", portfolio = portfolio, current_price = current_price)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

    if request.method == "POST":

        if not request.form.get("symbol"):
            flash('Please insert a symbol')
            return redirect(url_for('buy'))

        if not request.form.get("qty"):
            flash('Please insert quantity')
            return redirect(url_for('buy'))

        if int(request.form.get("qty")) < 1:
            flash('Quantity must be a positive integer')
            return redirect(url_for('buy'))

        r = lookup(request.form.get("symbol"))
        if r:

            total_cost = r['price'] * float(request.form.get("qty") );

            # check if user has enough money
            q = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"])

            if total_cost > q[0]['cash']:
                flash('Not enough money for the operation.')
                return redirect(url_for('buy'))
            else:

                # add to existing portfolio table?
                # MUST USE ON DUPLICATE KEY UPDATE
                # and it will merge / void the aquisition price, so do a new insertion
                insert_portfolio = db.execute(
                    "INSERT INTO portfolio (user_id, symbol, qty, unit_price) VALUES (:user_id, :symbol, :qty, :unit_price)",
                    user_id = session["user_id"],
                    symbol = request.form.get("symbol"),
                    qty = request.form.get("qty"),
                    unit_price = r['price']
                    )

                if insert_portfolio:

                    # subtract money from user account
                    update_cash = db.execute(
                        "UPDATE users SET cash = cash - :transaction_cost WHERE id =  :user_id",
                        user_id = session["user_id"],
                        transaction_cost = total_cost

                        )

                    # update session
                    session["user_cash"] = session["user_cash"] - total_cost

                    # log transaction
                    insert_transaction = db.execute(
                        "INSERT INTO transactions (user_id, action, symbol, qty, unit_price) VALUES (:user_id, :action, :symbol, :qty, :unit_price)",
                        user_id = session["user_id"],
                        action = "buy",
                        symbol = request.form.get("symbol"),
                        qty = request.form.get("qty"),
                        unit_price = r['price']
                        )

                    flash('transaction completed')
                    return redirect(url_for('index'))

                else:
                    flash('A problem happened with the database')
                    return redirect(url_for('buy'))

        else:

            flash('Symbol does not exist, or there was an error getting the quote.')
            return redirect(url_for('buy'))

    else:
        return render_template('buy.html')

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    # get transactions
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id = session["user_id"] )

    return render_template("history.html", transactions = transactions )

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submiting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["user_name"] = rows[0]["username"]
        session["user_cash"] = rows[0]["cash"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        symbols_test  = []

        with open('static/nasdaq.csv', newline='') as csvfile:
            symbols = csv.reader(csvfile, delimiter=',')
            # skip header
            next(symbols)
            for row in symbols:
                symbols_test.append(row)

        return render_template("get-quotes.html", symbols_test = symbols_test)

    else:
        quote = lookup(request.form.get("symbol"))
        return render_template("show-quotes.html", quote = quote)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    if request.method == "POST":
        # no user or white spaces
        if not request.form.get("username") or request.form.get("username").isspace():
            return "no user was provided"
        # no password or white spaces
        elif not request.form.get("password") or request.form.get("password").isspace():
            return "no password was provided or password is white spaces only"
        elif not request.form.get("password-retype"):
            return "no password retype was provided"
        elif request.form.get("password") != request.form.get("password-retype"):
            return "password and password confirmation don´t match"
        # everthing seems ok
        else:

            # insert into DB
            r = db.execute("INSERT INTO users ( username, hash) VALUES (:username, :hash)", username = request.form.get("username"), hash = pwd_context.encrypt(request.form.get("password")))
            return "result is: "+str(r)

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "POST":
        dict = request.form

        #print( dict )

        selled = 0

        for key in dict:

            if dict[key]  == "on":

                #print( key + " is selected, id is: "+dict[key+"-id"]+" and quantity is: "+dict[key+"-qty"]+" and current price is: "+dict[key+"-current-price"] )

                # delete if qty to sell is equal to the qty available
                if dict[key+"-qty"] == dict[key+"-qty-available"]:
                    db.execute("DELETE FROM portfolio WHERE id = :portfolio_id", portfolio_id = dict[key+"-id"])

                # if not 1 only, update qty
                else:
                    db.execute("UPDATE portfolio SET qty = qty - :qty WHERE id =  :portfolio_id", qty = dict[key+"-qty"], portfolio_id = dict[key+"-id"])

                # insert cash into user account
                sale_value = float(dict[key+"-current-price"]) * int(dict[key+"-qty"])
                print( sale_value ) # zero??
                db.execute("UPDATE users SET cash = cash + :value WHERE id = :user_id", value = sale_value, user_id = session["user_id"])

                # update session
                session["user_cash"] = session["user_cash"] + sale_value

                # log transaction
                db.execute("INSERT INTO transactions ( action, symbol, qty, user_id, unit_price ) VALUES ( 'sell', :symbol, :qty, :user_id, :unit_price )",
                symbol = dict[key+"-name"], qty = dict[key+"-qty"], user_id = session["user_id"], unit_price = dict[key+"-current-price"])

                selled = 1

        if selled:
            flash('Transaction was done with success')
            return redirect(url_for('sell'))
        else:
            flash('An error happened. Check if you selected at least one symbol to sell.')
            return redirect(url_for('sell'))

    # get current portfolio
    #portfolio = db.execute("SELECT symbol, SUM(qty) qty, unit_price, AVG(unit_price) as average_price, (unit_price*qty) total FROM portfolio WHERE user_id = :user_id GROUP BY symbol", user_id = 1 )
    portfolio = db.execute("SELECT id, symbol, qty, unit_price, (unit_price*qty) total FROM portfolio WHERE user_id = :user_id", user_id = session["user_id"] )

    # it would be nice to have the current price, and compare with the price that it was bought
    # DONE, but it´s not working ok, cause it´s grouping, and bought prices are different..

    current_price = []

    for item in portfolio:
        quote = lookup(item['symbol'])
        if quote:
            current_price.append({item['symbol'] : quote['price']})
        else:
            current_price.append({item['symbol'] : 0})

    return render_template("sell.html", portfolio = portfolio, current_price = current_price)

@app.route("/account", methods=["GET", "POST"])
@login_required
def account():

    if request.method == "POST":

        loaded_value = int(request.form.get("cash"))

        if db.execute("UPDATE users SET cash = cash + :value WHERE id = :user_id", value = loaded_value, user_id = session["user_id"]):

            # update session
            session["user_cash"] = session["user_cash"] + loaded_value

            flash("account was loaded with $"+ str(loaded_value) )

            return redirect(url_for("account"))

        else:
            flash("account was NOT loaded")
            return redirect(url_for("account"))

    return render_template('account.html')