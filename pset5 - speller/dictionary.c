// PBS @ CS50x
// 20.09.2017

/**
 * Implements a dictionary's functionality.
 */

/*
./speller dictionaries/small texts/pbs.txt
./speller texts/austinpowers.txt
check50 cs50/2017/x/speller

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

int dictionary_counter = 0;

//------------------------------------------------------------------------------
// struct of hash table

typedef struct node
{
    char word[LENGTH+1]; // maximum length for a word: 45
    struct node *next; // points to the next node
}

node;

// create hashtable
// with 26 buckets?
node *hash_table[26];

//------------------------------------------------------------------------------
/**
 * Hashes the char
 */
int hash( char first_char )
{

    int i = 0;

    if( isalpha( first_char ) )
    {

        // convert to lower case
        i = tolower( first_char ) - 97; // 97 is where ascii lower case start

    }

    return i;

}

//------------------------------------------------------------------------------
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{

    // transform to lowercase
    char buffer[LENGTH+1];

    // copy word into buffer
    strcpy(buffer, word);

    for( int i = 0; word[i] != '\0'; i++ )
    {
        if( isalpha( word[i] ) )
        {
            buffer[i] = tolower( word[i] );
        }

    }

    int first_char = hash(word[0]);
    // cursor to go to the right bucket
    node *cursor = hash_table[first_char];

    //printf("cursor is %p\n", cursor->word );
    //printf("cursor is %p\n", cursor );
    //printf("cursor is %s\n", cursor->word );
    //printf("cursor is %s\n", cursor->next );

    // we have an hash table for this char
    // something like hash_table[first_char], where first char is the int for s
    // and we have surf, surfer, start, and so on..
    while( cursor != NULL )
    {

        //printf("\n--- cursor is %p ---\n", cursor );
        //printf("\n--- cursor->word is %s ---\n", cursor->word );

        // compare generated word that is stored on the buffer
        // with the word pointed by the cursor
        if( strcmp( buffer, cursor->word ) == 0 )
        {
            //printf("check next cursor is %p\n", cursor->next);
            //printf("\nwe have a match between buffer (text) '%s' and cursor->word (dictionary) '%s' \n", buffer, cursor->word);
            return true;
            //return false;
        }
        else
        {
            //printf("\nwe don´t have a match between buffer (text) '%s' and cursor->word (dictionary) '%s', so move to cursor->next \n", buffer, cursor->word);
            cursor = cursor->next; // next..!
            //printf("check next cursor is %p\n", cursor->next);
        }

    }

    return false;

}

//------------------------------------------------------------------------------
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
//bool load(const char *dictionary)
bool load(const char *dictionary)
{

    // get a pointer to the file
    FILE *inptr = fopen( dictionary, "r");

    if( !inptr )
    {
        printf("dictionary was NOT loaded");
        return false;
    }

    // define dictionar word
    char dictionary_word[LENGTH+1];

    // scan file, while not the end
    while ( fscanf( inptr, "%s", dictionary_word ) != EOF )
    {

        dictionary_counter++;

        // create a new node to store the word from dictionary
        node *new_node = malloc(sizeof(node));

        // check if was created
        if ( !new_node )
        {
            unload();
            printf("\nERROR: unable to create new node\n");
            return false;
        }

        // copy dictionary word to new_node
        strcpy( new_node->word, dictionary_word );

        //printf("\n---- copying dictionary word %s to new_node->word ---\n", dictionary_word );

        // store it on the hash table
        // get first letter
        char first_char = dictionary_word[0];
        int index = hash( first_char );

        //printf("index is %i\n", index );

        // populate the hash table
        // if not assigned yet
        if( hash_table[index] == NULL )
        {
            //printf("index %i not created yet, populating the hash table with a new node stored at %p with the value of %s, and next node is %p", index, new_node, new_node->word, new_node->next);
            hash_table[index] = new_node;
            new_node->next = NULL;
        }
        else // already exists
        {
            new_node->next = hash_table[index];
            hash_table[index] = new_node;
        }

    }

    fclose( inptr );

    return true;


}

//------------------------------------------------------------------------------
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // if not loaded, returns 0
    return dictionary_counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{

    // loop thru buckets
    // then thru linked lists inside of the buckets..?
    for ( int i = 0; i < sizeof(hash_table); i++ )
    {

        if ( hash_table[i] != NULL )
        {
            //printf("hash table with index %i exists, loop thru it and delete nodes\n", i);

            node *cursor = hash_table[i];

            // recursive
            while ( cursor != NULL )
            {

                node *temp = cursor;

                /*
                printf("--- cursor to delete is %p ---\n", temp );
                printf("--- cursor->word to delete is %s ---\n", temp->word );
                printf("--- cursor->next to delete is %p ---\n", temp->next );
                */

                cursor = cursor->next;

                free( temp );

            }

            free( cursor );

            // if not deleted
            if( cursor )
                return false;

        }

    }

    return true;

}
