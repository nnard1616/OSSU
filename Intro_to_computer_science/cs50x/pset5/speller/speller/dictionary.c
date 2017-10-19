/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>
#include "dictionary.h"
node* root;
int number_of_dictionary_words = 0;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* trav = root;
    for (int i = 0; word[i] != '\0'; ++i)
    {
        // index of character:  a,b,c,...,y,z,' -> 0,1,2,...,24,25,26
        int char_index = tolower(word[i]) - 'a';

        // if char_index is negative, then it is a '\'' character.
        if (char_index < 0)
            char_index = 26;  // 'a' - '\'' = -58; set to 26

        // move to next node
        trav = trav->children[char_index];

        // Not sure why needed.
        if (trav != NULL)

            // if this is last char in word and current node represents a word,
            // then word was spelled correctly.
            if (word[i + 1] == '\0' && trav->is_word)
                return true;

        // if we've reached a null pointer and it isn't the end of our word,
        // then we've ended prematurely, not a word in dictionary.
        if (trav == NULL && word[i + 1] != '\0')
            return false;
    }


    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = malloc(sizeof(node));
    FILE* fp = fopen(dictionary, "r");

    if (fp == NULL)
        return false;

    int index = 0;
    char word[LENGTH + 1];

    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            word[index] = c;
            index++;

            // ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // consume remainder of alphabetical string
                while ((c = fgetc(fp)) != EOF && isalpha(c))
                    ;

                // prepare for new word
                index = 0;
            }
        }

        // ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // consume remainder of alphanumeric string
            while ((c = fgetc(fp)) != EOF && isalnum(c))
                ;

            // prepare for new word
            index = 0;
        }

        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';

            // pointer to traverse trie structure
            node* trav = root;

            // add each of word's char info onto trie structure
            for (int i = 0; word[i] != '\0'; ++i)
            {
                // index of character:  a,b,c,...,y,z,' -> 0,1,2,...,24,25,26
                int char_index = tolower(word[i]) - 'a';

                // if char_index is negative, then it is a '\'' character.
                if (char_index < 0)
                    char_index = ALPHAS - 1;  // 'a' - '\'' = -58; set to 26

                // if char in sequence hasn't been added yet, then add it
                if (trav->children[char_index] == NULL)
                {
                    trav->children[char_index] = malloc(sizeof(node));
                    trav = trav->children[char_index];
                }

                // if char in sequence was already added previously, move on
                else
                    trav = trav->children[char_index];

                // if we've reached end of word, then record it on trie
                if (word[i + 1] == '\0')
                {
                    trav->is_word = true;
                    number_of_dictionary_words++;
                }
            }


            // prepare for next word
            index = 0;
        }
    }
    return true;  // successfully loaded dictionary
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return number_of_dictionary_words;
}

void unload_helper(node* prev)
{
    // If all childrend are null pointers, end of recursion branch
    int null_counter = 0;
    for (int i = 0; i != ALPHAS; ++i)
        if (prev->children[i] == NULL)
            null_counter++;

    if (null_counter == ALPHAS)
    {
        free(prev);  // set free the memory
        return;      // end recursion branch
    }

    // recurse through all trie branches
    for (int i = 0; i != ALPHAS; ++i)
        if (prev->children[i] != NULL)
            unload_helper(prev->children[i]);
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    unload_helper(root);
    return true;
}
