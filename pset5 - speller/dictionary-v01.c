/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "dictionary.h"

//------------------------------------------------------------------------------
// struct of hash table

typedef struct node
{
    char word[LENGTH+1]; // maximum length for a word: 45
    struct node *next; // points to the next node
}

node;

//------------------------------------------------------------------------------
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    return false;
}

//------------------------------------------------------------------------------
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
//bool load(const char *dictionary)
bool load(const char *dictionary)
{
    // TODO

    // get a pointer to the file
    FILE *inptr = fopen( dictionary, "r");

    //uint8_t buffer[512];
    char buffer[sizeof(char)];

    int bytes_read = 0;

    printf("open dictionary: %s\n", dictionary);

    if( inptr )
    {
        printf("dictionary was loaded\n");

        // go to end of file
        fseek(inptr, 0, SEEK_END);

        // get the file size
        int size = ftell( inptr );

        printf("size is %i bytes\n", size);

        // back to the start
        rewind( inptr );

        bytes_read = fread(&buffer, size + 1, 1, inptr);

        //printf("first byte is: %hhu\n", buffer[0]);

        printf("first byte is: %c\n", buffer[0]);

        //printf("content of file is: \n%s", buffer);

        return false;

        //return true;
    }
    else
    {
        printf("dictionary was NOT loaded");
        return false;
    }

}


//------------------------------------------------------------------------------
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
