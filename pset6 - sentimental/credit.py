import cs50


def main():

    print("insert credit card number")

    while True:

        cc_number = cs50.get_int()
        # cc_number = 4242424242424242 # visa
        # cc_number = 340000000000000 # invalid
        # cc_number = 378282246310005 # amex
        # cc_number = 5105105105105100 # mastercard

        if(cc_number > 0):
            break

    # auxiliar vars

    cc_number_divided = cc_number
    every_other_second = 0
    every_other_second_result = 0
    other_digits_result = 0

    # divide the cc number by 100, until it´s greater than zero
    # /= Division assignment

    while cc_number_divided > 1:

        cc_number_divided = int(cc_number_divided)  # cast to integer
        # print(cc_number_divided)

        # excludes the last digit, then gets the remainder
        every_other_second = cc_number_divided / 10 % 10

        #print( every_other_second )

        # gets the last two digits?
        x = int(every_other_second) * 2
        #print( x )

        if(x > 9):

            #print("is > 9")

            # first digit
            every_other_second_result += x / 10

            # second digit
            every_other_second_result += x % 10

        else:

            #print("is < 9");
            every_other_second_result += x

        other_digits_result += cc_number_divided % 10

        # print(other_digits_result)

        # division assignment
        cc_number_divided /= 100

        #print( every_other_second_result + other_digits_result )

    # checksum passes
    if((int(every_other_second_result + other_digits_result)) % 10 == 0):

        # now check which type it is
        if((cc_number >= 340000000000000 and cc_number < 350000000000000) or (cc_number >= 370000000000000 and cc_number < 380000000000000)):
            print("AMEX\n")
        elif((cc_number >= 4000000000000 and cc_number < 5000000000000) or (cc_number >= 4000000000000000 and cc_number < 5000000000000000)):
            print("visa")
        elif(cc_number >= 5100000000000000 and cc_number < 5600000000000000):
            print("mastercard")
    else:
        print("invalid")


if __name__ == "__main__":
    main()
