#include "dictionary.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 45
#define NUM_BUCKETS 100

typedef struct Node
{
    char word[MAX_WORD_LENGTH];
    struct Node *next;
} Node;

Node *hashTable[NUM_BUCKETS];

unsigned int hash(const char *word)
{
    return (unsigned int) word[0] % NUM_BUCKETS;
}

bool check(const char *word)
{
    char lowercaseWord[MAX_WORD_LENGTH];
    for (int i = 0; word[i] != '\0'; ++i)
    {
        lowercaseWord[i] = tolower(word[i]);
    }
    lowercaseWord[strlen(word)] = '\0';

    unsigned int bucket = hash(lowercaseWord);

    for (Node *current = hashTable[bucket]; current != NULL; current = current->next)
    {
        if (strcmp(current->word, lowercaseWord) == 0)
        {
            return true;
        }
    }

    return false;
}

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char currentWord[MAX_WORD_LENGTH];

    while (fscanf(file, "%s", currentWord) != EOF)
    {
        Node *newNode = malloc(sizeof(Node));
        if (newNode == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(newNode->word, currentWord);
        unsigned int bucket = hash(currentWord);
        newNode->next = hashTable[bucket];
        hashTable[bucket] = newNode;
    }

    fclose(file);
    return true;
}

unsigned int size(void)
{
    unsigned int wordCount = 0;

    for (int i = 0; i < NUM_BUCKETS; ++i)
    {
        for (Node *current = hashTable[i]; current != NULL; current = current->next)
        {
            wordCount++;
        }
    }

    return wordCount;
}

bool unload(void)
{
    for (int i = 0; i < NUM_BUCKETS; ++i)
    {
        Node *current = hashTable[i];
        while (current != NULL)
        {
            Node *nextNode = current->next;
            free(current);
            current = nextNode;
        }
        hashTable[i] = NULL;
    }

    return true;
}
