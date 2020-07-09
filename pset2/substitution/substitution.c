#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//function prototypes
int keyValidation(string key);
void encipher(string text, string key);

int main(int argc, string argv[])
{

    // check for single command line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check for key validation, if valid cipher the plaintext
    if (keyValidation(argv[1]) == 0)
    {
        // prompt the use for plaintext if the key is valid
        string getText = get_string("plaintext: ");

        // print out ciphered text
        printf("ciphertext: ");
        encipher(getText, argv[1]);
    }
    else
    {
        return 1;
    }
    return 0;
}

// this function take a string and find character that is repeated.
int keyValidation(string key)
{
    int len = strlen(key);

    // iterate over each character
    for (int i = 0; i < len; i++)
    {
        // check for alphabetic characters
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        // check the length of the string which is 26 equivalent to alphabet characters.
        if (len != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        // check for repeated characters
        for (int j = i + 1; j < len; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }

    }
    return 0;
}

// cipher the plaintext into the key
// takes two string plaintext and the key.
void encipher(string text, string key)
{
    //iterate over the plaintext
    int textLength = strlen(text);
    for (int i = 0; i < textLength; i++)
    {
        // change the plaintext letters into the correct index of alphabet key letters.
        if (isupper(text[i]))
        {
            text[i] = toupper(key[text[i] - 65]);
        }
        else if (islower(text[i]))
        {
            text[i] = tolower(key[text[i] - 97]);
        }

    }
    string cipherText = text;
    printf("%s\n", cipherText);
    return;
}