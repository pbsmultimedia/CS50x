# PBS @CS50x
# 10.10.2017
# Implement a program that encrypts messages using Caesar’s cipher
# conversion from C

import cs50


def main():
    print("please insert your cypher key:")

    # get key
    while True:
        key = cs50.get_int()

        if(key < 0):
            print("non-negative integers only")
        else:
            break

    # get plain text
    while True:

        print("please insert plain text:")

        text = cs50.get_string()

        if(text == ""):
            print("please insert plain text:")
        else:
            break

    # ok, we got key and text
    # loop thru string chars..

    alphabetical_index = 0
    remain = 0
    ascii_start = 0

    for c in text:

        # print(c)

        # validate char as alphabetic
        if(c.isalpha()):

            # know where to start counting on ASCII table
            # if lower, starts at 97
            if(c.islower()):
                ascii_start = 97
            else:
                ascii_start = 65

            # print(ascii_start)

            # calculates alpha index, example: "a" = 65 - 65 = 0
            alphabetical_index = ord(c) - ascii_start

            # print(alphabetical_index)

            # remainder of 26 ( chars ) that is the offset
            remain = (alphabetical_index + key) % 26

            # print("the remain is %i \n", remain );

            # add the offset ( remain ) to ascii_start
            # to get the ascii number of the cyphered char
            print(chr(ascii_start + remain), end="")

        else:
            # we have symbol or numeric char
            print(c, end="")

    print("")


if __name__ == "__main__":
    main()
