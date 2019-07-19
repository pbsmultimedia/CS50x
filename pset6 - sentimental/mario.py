# http://docs.cs50.net/2017/x/psets/6/pset6.html

import cs50


def main():
    print("Type pyramid height: ");

    while True:
        height = cs50.get_int()

        if height > 0 and height < 24:
            break

        else:
            print("height is invalid, insert a positive integer, smaller than 24")

    for loop in range(height):
        draw_pyramid_row(height, loop)
        print("")

# receives the height and current loop
# draws a row with the current


def draw_pyramid_row(height, loop):

    for i in range(height):
        if i < height - (loop + 1):
            print(" ", end="")
        else:
            print("#", end="")

    # separator
    print("  ", end="")

    # right side
    for i in range(loop + 1):
        print("#", end="")


if __name__ == "__main__":
    main()
