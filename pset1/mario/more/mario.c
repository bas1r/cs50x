#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n > 8 || n < 1);
    //the right-angled pyramid.
    //This loop controls the row.
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
        
        //The left-angle pyramid.
        printf("  ");

        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");

    }

}
