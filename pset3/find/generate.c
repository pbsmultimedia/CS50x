/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    
   //printf( "argc: %i \n", argc );
    
    // give feedback if no number and seed is provided
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // convert argv[1] string to an integer
    int n = atoi(argv[1]);

    // if seed is given
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }
    
    /*
    The function srand48() is used to seed, or initialize, the internal buffer of functions such as drand48(). 
    You normally seed drand48() with something like time(NULL) since this value will always change. 
    If you were to simply call drand48() without seeding it, you’d get the same string of random doubles back.
    */
    
    // loop to create and print the required n random numbers
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
