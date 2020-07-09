# double pyramid height between 1 to 8


from cs50 import get_int


def main():

    userInput = get_positive_int()  # getting user input

    for i in range(1, userInput + 1):  # printing pyramid
        print(" " * (userInput - i) + "#" * i + "  " + "#" * i)


def get_positive_int():  # prompt user for positive integer between 1 to 8
    while True:
        n = get_int("Pyramid height: ")
        if n > 0 and n < 9:
            break
        print("Enter number between 1 to 10")
    return n


main()