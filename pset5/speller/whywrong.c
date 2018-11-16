// Implements a dictionary's functionality

#include <stdbool.h>
#include<cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

node *root;
int counter = 0;

node *getNode(void)
{
    node *newNode = malloc(sizeof(node));

    if (newNode != NULL)
    {
        newNode->is_word = false;

        for (int i = 0; i < 27; i++)
        {
            newNode->children[i] = NULL;
        }
    }

    return newNode;
}

void freeSpace(node* end)
{
    for (int i = 0; i < 27; i++)
    {
        if(end->children[i] != NULL)
        {
            freeSpace(end->children[i]);
        }
    }
    free(end);
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node* pointer = root;
    int num = 0;
    bool isword = false;

    for (int i = 0; word[i] != '\0'; i++) ??
    {
        if (isalpha(word[i])) ??
        {
            num = tolower(word[i]) - 'a';
        }
        else if(word[i] == '\'')
        {
            num = 26;
        }
        printf("%i\n",num);
        pointer = pointer->children[num];
        if(pointer == NULL)
        {
            return false;
        }
    }

    isword = pointer->is_word;
    return isword;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int num = 0;
    root = getNode();
    if(root == NULL)
    {
        return false;
    }


    FILE *dic = fopen(dictionary,"r");
    if (dic == NULL)
    {
        printf("File does not exist.\n");
        return false;
    }

    for(int c = fgetc(dic); c != EOF; c = fgetc(dic))
    {
        node* pointer = root;
        if (c != '\n')
        {
            if (isalpha(c))
            {
                num = c - 'a';
            }
            else if(c == '\'')
            {
                num = 26;
            }

            if (pointer->children[num]  == NULL)
            {
                pointer->children[num] = getNode();
                if (pointer->children[num] == NULL)
                {
                    return false;
                }
            }

            pointer = pointer->children[num];
        }
        else
        {
            pointer->is_word = true;
            counter++;
        }
    }

    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (counter > 0)
    {
        return counter;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if(root != NULL)
    {
        node* pointer = root;
        freeSpace(pointer);
        return true;
    }
    else
    {
        return false;
    }
}
