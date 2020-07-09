//CS50x pset1 - 2020 mario/less
#include <cs50.h>
#include <stdio.h>

//This program create a right-angled pyramid between number 1 and 8.
int main(void)
{
    //prompt user for input 
    int n; 
    do
    {
        n = get_int("Height: ");
    }
    while (n > 8 || n < 1);

    //This loop controls rows.
    for (int i = 0; i < n; i++)
    {
        //This loop controls spaces
        for (int j = 1; j < n - i; j++)
        {
            printf(" ");
        }
        
        //This loop controls hashes
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");  
    }

}

