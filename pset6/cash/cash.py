from cs50 import get_float


def main():  # main function

    # output total number of used coins
    print(coinNum())


def askPositiveFloat():  # prompt and validate user's input
    while True:
        positiveFloat = get_float("Change Owed: ")

        if positiveFloat > 0:
            break

    return positiveFloat


def coinNum():  # track coins
    # ask for change and round the change
    totalCents = round(askPositiveFloat() * 100)

    # coin values
    quarter = 25
    dime = 10
    nickel = 5
    penny = 1

    # coins used
    quarterUsed = 0
    dimeUsed = 0
    nickelUsed = 0
    pennyUsed = 0

    if totalCents >= quarter:  # check coins
        quarterUsed = int(totalCents / quarter)
        totalCents = totalCents - (quarterUsed * quarter)

    if totalCents >= dime:
        dimeUsed = int(totalCents / dime)
        totalCents = totalCents - (dimeUsed * dime)

    if totalCents >= nickel:
        nickelUsed = int(totalCents / nickel)
        totalCents = totalCents - (nickelUsed * nickel)

    if totalCents >= penny:
        pennyUsed = int(totalCents / penny)
        totalCents = totalCents - (pennyUsed * penny)

    return (quarterUsed + dimeUsed + nickelUsed + pennyUsed)


main()