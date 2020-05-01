// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5381;
/*
  Some large prime, used for total number of buckets
  i.e. the total size of the hash table array
*/

// Hash table
node *table[N];
bool loaded = false;
unsigned int dict_size = 0;

/*
    Add word to dictionary, update size of dictionary
    Takes addresses of pointers of prev and current nodes
*/
bool add_word(node **current, node **prev, const char *word)
{
    // Allocate memory for new node
    *current = malloc(sizeof(node));
    if (*current == NULL)
    {
        return false;
    }

    if (prev != NULL)
    {
        (*prev)->next = *current;
    }
    strcpy((*current)->word, word);
    (*current)->next = NULL;

    dict_size++;
    return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    unsigned int index, word_length;
    node *current = NULL, *prev = NULL;

    // Get line by line from dictionary until end of file
    while (fgets(word, LENGTH + 1, dict))
    {
        word_length = strlen(word);
        // Remove newline at the end of word
        if (word[word_length - 1] == '\n')
        {
            // Ignore plain blank lines
            if (word_length == 1)
            {
                continue;
            }
            word[word_length - 1] = '\0';
        }

        index = hash(word);
        current = table[index];

        // If there is no word in this index
        if (current == NULL)
        {
            if (!add_word(&current, NULL, word))
            {
                return false;
            }
            // Add new node in calculated index
            table[index] = current;
            continue;
        }

        // If there is already a node in this index
        while (current->next != NULL)
        {
            current = current->next;
        }
        // Set previous and current node pointers
        prev = current;
        current = current->next;
        // Add new node to linked list
        if (!add_word(&current, &prev, word))
        {
            return false;
        }
    }

    loaded = true;
    fclose(dict);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash = hash + (i + 1) * word[i];
    }
    return hash % N;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (!loaded)
    {
        return 0;
    }

    return dict_size;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Make sure everything is lowercase before hashing
    char check_word[LENGTH + 1];
    strcpy(check_word, word);

    for (int i = 0; i < strlen(word); i += 1)
    {
        check_word[i] = tolower(check_word[i]);
    }

    unsigned int index = hash(check_word);
    node *current = table[index];

    if (current == NULL)
    {
        return false;
    }

    // Check in linked list if word exists
    do
    {
        int res = strcmp(current->word, check_word);
        if (res == 0)
        {
            return true;
        }
        current = current->next;
    }
    while (current != NULL);

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *current, *prev;
    for (int i = 0; i < N; i += 1)
    {
        if (table[i] != NULL)
        {
            prev = table[i];
            current = prev->next;
            free(prev);

            while (current != NULL)
            {
                prev = current;
                current = current->next;
                free(prev);
            }
        }
    }
    return true;
}
