// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Total words in dictionary
unsigned int total_words = 0;

// Creating a node for each word
node *hash_node = NULL;

// Number of buckets in hash table
const unsigned int N = 500000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Getting index value of given word in hashtable
    int index = hash(word);

    if (table[index] == NULL)
    {
        return false;
    }
    // Pointing at the first element of hashtables index index
    node *cursor = table[index];
    for (; ;)
    {
        // Checking if that given word is in dictionary or not
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        if (cursor->next != NULL)
        {
            cursor = cursor->next;
        }
        else
        {
            break;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Creating a string buffer to addstrings from file
    char words[LENGTH + 1];
    int index;
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Scanning 1 word from a line and adding it to buffer
    while (fscanf(file, "%s", words) != EOF)
    {
        total_words++;
        hash_node = malloc(sizeof(node));
        if (hash_node == NULL)
        {
            return false;
        }
        strcpy(hash_node->word, words);
        // Generating hashcode for that word
        index = hash(words);
        // Adding node in hashtable
        if (table[index] != NULL)
        {
            hash_node->next = table[index];
            table[index] = hash_node;
        }
        // Else adding first node at index index
        else
        {
            table[index] = hash_node;
            table[index]->next = NULL;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return total_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Freeing each node
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *cursor = table[i];
            table[i] = table[i]->next;
            free(cursor);
        }
    }
    return true;
}