// Implements a dictionary's functionality

#include <stdbool.h>
#include<cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#include "dictionary.h"

//type define struct node
typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

node *root;
int counter = 0;

//get new node
node *getNode(void)
{
    node *newNode = malloc(sizeof(node));

    //initialize
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

//free space using recursion
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

    //find the word
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            num = tolower(word[i]) - 'a';
        }
        else if(word[i] == '\'')
        {
            num = 26;
        }

        pointer = pointer->children[num];
        if(pointer == NULL)
        {
            return false;
        }
    }

    //check is_word
    isword = pointer->is_word;
    return isword;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int num = 0;
    char word[LENGTH+1];
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

    //scan word
    while(fscanf(dic, "%s\n", word) != EOF)
    {
        node* pointer = root;

        //store word
        for (int i = 0; word[i] != '\0'; i++)
        {
            if (isalpha(word[i]))
            {
                num = word[i] - 'a';
            }
            else if(word[i] == '\'')
            {
                num = 26;
            }

            //if children is NULL, create new node
            if (pointer->children[num]  == NULL)
            {
                pointer->children[num] = getNode();
                if (pointer->children[num] == NULL)
                {
                    return false;
                }
            }

            //point to children
            pointer = pointer->children[num];
        }

            //set is_word true
            pointer->is_word = true;
            counter++;

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
