//CS50 Problem Set 2 (2020): Readability test
//Author: basir

#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>

int countLetters(string n);
int countWords(string n);
int countSntns(string n);
int gradeIndex(float l, float  w, float s);

int main(void)
{
    // get text from user.
    string getText = "";
    do
    {
        getText = get_string("Text: ");

    }
    while (strlen(getText) < 0);

    // printf("%i Letter(s) %i Word(s) %i Sentence(s)\n", countLetters(getText), countWords(getText), countSntns(getText));

    int grade = gradeIndex(countLetters(getText), countWords(getText), countSntns(getText));

}


// using the characters in the context of numerical values it automatically changes to it’s ASCII value.
// this function count the letter
int countLetters(string n)
{
    int counter = 0;
    for (int i = 0; i < strlen(n); i++)
    {
        if (isalpha(n[i]))
        {
            counter++;
        }
    }
    return counter;
}

// this function counts the words
int countWords(string n)
{
    int counter = 1;
    for (int i = 0; i < strlen(n); i++)
    {
        if (isblank(n[i]))
        {
            counter++;
        }
    }
    return counter;
}

// this function counts the sentences
int countSntns(string n)
{
    int counter = 0;
    for (int i = 0; i < strlen(n); i++)
    {
        if (n[i] == '.' || n[i] == '!' || n[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}


// One such readability test is the Coleman-Liau index. The Coleman-Liau index of a text is designed to output what (U.S.) grade level is needed to understand the text.
// The formula is: index = 0.0588 * L - 0.296 * S - 15.8  Here, L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.

int gradeIndex(float L, float  W, float S)
{

    int grade = 0;
    L = 100 * L / W;
    S = 100 * S / W;

    float g = round(0.0588 * L - 0.296 * S - 15.8);

    if (g < 16 && g >= 0)
    {
        printf("Grade %i\n", (int) g);
    }
    else if (g >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (g < 0)
    {
        printf("Before Grade 1\n");
    }

    return grade;

}