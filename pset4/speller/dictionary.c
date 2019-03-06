// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

void destroy(node *);

// Represents a hash table
node *hashtable[N];

// Head pointers
node *head[N];

// Traversal pointer
node *trav;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Store integer hash
        const short int index = hash(word);

        // Malloc a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // Copy dictionary word into the node
        strcpy(new_node->word, word);

        // Insert into linked list
        new_node->next = head[index];
        head[index] = new_node;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    // Repeat hashtable times
    for (int i = 0; i < N; i++)
    {
        trav = head[i];
        while (trav != NULL)
        {
            count++;
            trav = trav->next;
        }
    }
    return count;
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Temporary editable storage
    char *lowerword = malloc(strlen(word) + 1);
    strcpy(lowerword, word);

    // Make lowercase
    for (int i = 0, j = strlen(lowerword); i < j; i++)
    {
        lowerword[i] = tolower(lowerword[i]);
    }

    // Hash for index
    const short int index = hash(lowerword);

    // Initialise traversal node
    trav = head[index];

    // Search for word
    while (trav != NULL)
    {
        if (strcmp(trav->word, lowerword) == 0)
        {
            free(lowerword); 
            return true;
        }
        else
            trav = trav->next;
    }

    free(lowerword);
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    short int i = 0;

    // Iterate through every 'bucket'
    for (i = 0; i < N; i++)
    {
        trav = head[i];
        destroy(trav);
    }

    if (i == 26)
        return true;
    else
        return false;
}

void destroy(node *cur)
{
    // Base case
    if (cur == NULL)
        return;
    // Recursive case        
    else
    {
        trav = cur;
        cur = cur->next;
        free(trav);
        destroy(cur);
    }
}