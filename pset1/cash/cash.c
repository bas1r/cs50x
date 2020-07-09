#include <cs50.h>
#include <stdio.h>
#include <math.h>

float askPositiveFLoat(void);
int coinNum();


int main(void)
{
    printf("%i\n", coinNum());
}




//Function that prompt the user input and validate 
float askPositiveFloat(void)
{
    //ask user for number
    float positiveFloat;
    
    do
    {
        positiveFloat = get_float("Change Owed: ");

    }
    while (positiveFloat < 0);

    return positiveFloat;
}

//This function track the coins
int coinNum()
{
    //gets user input and turns it into number of total cent with help of round from math.h library.
    int totalCents = round(askPositiveFloat() * 100);

    //Variable to store coin count
    int numOfCoins = 0;

    //Variable to store remainder
    int remainder;

    // variable to store temporary number for division 
    int tempNum;

    // coin values 
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    // cascading down the coins from biggest to smallest.
    
    if (totalCents >= quarter)
    {
        remainder = totalCents % quarter;
        tempNum = totalCents - remainder;
        numOfCoins = numOfCoins + (tempNum / quarter);
        totalCents = remainder;

    }

    if (totalCents >= dime)
    {
        remainder = totalCents % dime;
        tempNum = totalCents - remainder;
        numOfCoins = numOfCoins + (tempNum / dime);
        totalCents = remainder;

    }

    if (totalCents >= nickel)
    {
        remainder = totalCents % nickel;
        tempNum = totalCents - remainder;
        numOfCoins = numOfCoins + (tempNum / nickel);
        totalCents = remainder;
    }

    if (totalCents >= penny)
    {
        remainder = totalCents % penny;
        tempNum = totalCents - remainder;
        numOfCoins = numOfCoins + (tempNum / penny);
        totalCents = remainder;
    }

    return numOfCoins;
}
