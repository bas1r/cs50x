// Implements a dictionary's functionality
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include <stdbool.h>

#include "dictionary.h"

// dictoionary word counter
int dictWordCounter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 60000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    node *search = table[index];

    while (search != NULL)
    {

        if (strcasecmp(search->word, word) == 0)
        {
            return true;
        }
        else
        {
            search = search->next;
        }
    }
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    unsigned long hash =  5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);

    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // create a FILE pointer adn fopen to start the stream
    FILE *file = fopen(dictionary, "r");

    // a place to store the current word in the loop
    char words[LENGTH + 1] = {'\0'};

    if (file == NULL)
    {
        unload();
        return false;
    }


    // fscanf give us whatever we say in the format argument (like %s)
    // and put into testString

    while (fscanf(file, "%s", words) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        strcpy(n->word, words);

        int index = hash(words) % N;

        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        dictWordCounter++;
    }
    fclose(file);

    printf("%i\n", dictWordCounter);

    // TODO
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictWordCounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    // TODO
    return true;
}
