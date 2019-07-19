/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

/*
Your implementation must return false immediately if n is non-positive.
Your implementation must return true if value is in values and false if value is not in values.
The running time of your implementation must be in O(log n).
You may not alter the function’s declaration. 
*/
 
bool search(int value, int values[], int n)
{
    
    if( n == 0 )
        return false;
  
    // find the middle of the array  
    int middle = n / 2;
    
    /*
    printf("\n-------------------------------------------------\n");
    
    printf("searching for value %i on: \n", value);
    
    for( int i = 0; i < n; i++ )
    {
        
        printf( "%i, ", values[i] );
        
    }
    
    printf("\ntotal numbers are %i \n", n);
    
    printf("middle array key is: %i \n", middle );
    
    printf("\n-------------------------------------------------\n");
    */
    
    if( value == values[ middle ] )
    {
     
        //printf("found it! should exit here..?");
        return true;
        
    }
    
    // search to the left - could be a function that serves both sides..
    else if( value < values[ middle ] )
    {
        
        //printf("\nsearching to the left\n");
        
        // assign the left part of the original array to the new array
        // create a new array and store the new values
        
        int new_array [ middle ];
        
        int i;
        
        for( i = 0; i < middle; i++ )
        {
            
            new_array[ i ] = values[ i ];
            
        }
        
        // break the recursion
        if( search( value, new_array, i ) )
            return true;
        
    }
    
    // search to the right
    else if( value > values[ middle ] )
    {
        
        // assign the left part of the original array to the new array
        // create a new array and store the new values
        
        //printf("search to the right.. \n");
        
        int new_array [ middle ];
        
        // will store the middle
        int i;
        
        // start counting from 0
        int x = 0;
        
        for( i = middle + 1; i < n; i++ )
        {
            
            //printf( "%i \n", values[ i ] );
            new_array[ x ] = values[ i ];
            //printf( "remainder array is %i \n", new_array[ i ] );
            
            x++;
            
        }
        
        // break the recursion
        if( search( value, new_array, x ) )
            return true;
        
    }    
    
    return false;
    
}

void swap( int *a, int *b )
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

/**
 * Sorts array of n values.
 */
 
/*

Your implemenation must sort, from smallest to largest, the array of numbers that it’s passed.

The running time of your implementation must be in O(n2), where n is the array’s size. - bubble sort

You may not alter the function’s declaration. Its prototype must remain:

O(N2) represents an algorithm whose performance is directly proportional to the square of the size of the input data set. 
This is common with algorithms that involve nested iterations over the data set. Deeper nested iterations will result in O(N3), O(N4) etc.

*/
 
void sort(int values[], int n)
{
    for( int loop = 0; loop < n -1; loop++) // -1 because N numbers can only make N-1 pairs
    {
        if( values[loop + 1] < values[loop] )
        {
            swap( &values[loop], &values[loop + 1] );
            sort( values, n );
        }
    }
    return;
}