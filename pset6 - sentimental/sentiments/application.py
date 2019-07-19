from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer

import os
import sys

import helpers

from analyzer import Analyzer

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)

    if(tweets == None):
        error = "there was an error getting tweets from " + screen_name
        return render_template("error.html", error=error)

    positive = negative = neutral = 0

    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    tweets_list = []

    for tweet in tweets:

        score = 0

        # this tweet analyzer - get new score
        analyzer = Analyzer(positives, negatives)

        # know must loop thru each word, and analyze it
        words = tweet.split()

        for word in words:

            score = analyzer.analyze(word)

            #x.append( [['score',score], ['tweet',tweet]] )

            if(score > 0):
                positive += 1
            elif(score < 0):
                negative += 1
            else:
                neutral += 1

        # list_of_dicts = [{'first_name':'greg', 'last_name':'schlaepfer'},
        #x.append( [{'score': score , 'tweet' : tweet}] )
        tweets_list.append({'score': score, 'text': tweet})

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name, positive=positive, negative=negative, neutral=neutral, tweets_list=tweets_list)
