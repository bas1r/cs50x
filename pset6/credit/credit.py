#  this program prompts the user for a credit card number
#  reports whether it is a valid American Express, MasterCard or Visa card.


from cs50 import get_int
import sys


def main():  # main function
    usage()

    cardNumber = get_int("Number: ")  # prompt user for input
    validate(cardNumber)


def usage():
    msg = """

SYNOPSIS
        python3 {}
        Number: [CREDIT CARD NUMBER]

    """.format(sys.argv[0])

    print(msg)


def validate(cc):  # validate credit card number
    tempList = [int(c) for c in str(cc)]

    listOne = tempList[-2::-2]  # second-to-last digit of credit card
    listTwo = tempList[::-2]  # remaining digits

    totalSum = sum(listTwo)
    for digit in listOne:
        totalSum += sum(divmod(2 * digit, 10))

    valid = totalSum % 10 == 0

    # check credit card's brands
    if tempList[0] == 4 and len(tempList) >= 13 and len(tempList) <= 16 and valid:
        print("VISA")
    elif tempList[0:2:] == [5, 1] or tempList[0:2:] == [5, 5] and len(tempList) == 16 and valid:
        print("MASTERCARD")
    elif tempList[0:2:] == [3, 4] or tempList[0:2:] == [3, 7] and len(tempList) == 15 and valid:
        print("AMEX")
    else:
        print("INVALID")


main()