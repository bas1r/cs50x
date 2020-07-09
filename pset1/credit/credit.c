#include <stdio.h>
#include <cs50.h>

// this program prompts the user for a credit card number and then reports whether it is a valid American Express, MasterCard, Visa card number.

int main()
{
    // prompt the user for input
    long long askCardNum = get_long_long("Number: ");

    // delcare variables
    int digitOne = 0;
    int digitTwo = 0;
    int numOfDigits = 0;
    int sumOfDoubleOdds = 0;
    int sumOfEvens = 0;

    // On iteration this loop do the checksum and validate
    while (askCardNum > 0)
    {
        digitTwo = digitOne;
        digitOne = askCardNum % 10;

        if (numOfDigits % 2 == 0)
        {
            sumOfEvens = sumOfEvens + digitOne;
        }
        else 
        {
            int multiply = 2 * digitOne;
            sumOfDoubleOdds += (multiply / 10) + (multiply % 10);
        }
        askCardNum = askCardNum / 10;
        numOfDigits++;
    }


    // report for the user

  
    bool valid = (sumOfEvens + sumOfDoubleOdds) % 10 == 0;
    int firstTwoDigits = (digitOne * 10) + digitTwo;

    if (digitOne == 4 && numOfDigits >= 13 && numOfDigits <= 16 && valid)
    {
        printf("VISA\n");
    }
    else if (firstTwoDigits >= 51 && firstTwoDigits <= 55 && numOfDigits == 16 && valid)
    {
        printf("MASTERCARD\n");
    }
    else if ((firstTwoDigits == 34 || firstTwoDigits == 37) && numOfDigits == 15 && valid)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
    
}
