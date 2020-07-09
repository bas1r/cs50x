#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    int key;


    // This checks if there is only 2 arguments.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


    // if argc is equal to 2, then running a loop that checks to ensure that every character is a digit.
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            // to convert string to number we use atoi in stdlib.h library.
            key = atoi(argv[1]); //get the caesar key value convert into integer
        }
    }


    string getText = ""; // get plain text from the user
    do
    {
        getText = get_string("Plaintext: "); // get plain text from the user
    }
    while (strlen(getText) == 0);

    printf("ciphertext: "); //print out cipher text

    // on each iterate n times checks each individual character of the string letter by letter

    int n = strlen(getText); // the strlen() function calculates the length of a given string in this case plaintext.
    for (int i = 0; i < n; i++)
    {
        // this figure out whether the number is lowercase or smallcase
        // using the characters in the context of numerical values it automatically changes to it’s ASCII value.
        // checking if it is lowercase 97 = a to 112 = z and if it + 13 characters along.
        if (getText[i] >= 'a' && getText[i] <= 'z')
        {
            printf("%c", (getText[i] - 'a' + key) % 26 + 'a'); // print out lowercase with key
        }// if it is between uppercase A and Z
        else if (getText[i] >= 'A' && getText[i] <= 'Z')
        {
            printf("%c", (getText[i] - 'A' + key) % 26 + 'A'); // print out uppercase with key
        }
        else
        {
            printf("%c", getText[i]);
        }
    }

    printf("\n");
    return 0;
}