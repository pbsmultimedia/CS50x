// PBS @ CS50x
// 24.07.2017
// Implement a program that, given a person’s name, prints a person’s initial

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main( void )
{
    
    string name = "";
    
    do{
        
        name = get_string();
        
    }
    
    // ask for name while it´s empty
    while( name[0] == '\0' );
    
    // * will place the var in the read-only parts of the memory, and making a pointer to that makes any writing operation on this memory illegal.
    char *array[10];
    int i = 0;
    
    // explode the name
    array[i] = strtok(name, " ");
    
    while(array[i] != NULL)
    {
        printf("%c", toupper( array[i][0] ));
        // strtok() keeps some data in static variables inside the function itself so it can continue a searching from the point it left it the previous call. 
        // To signal strtok() that you want to keep searching the same string, you pass a NULL pointer as its first argument. strtok() checks whether it is NULL and if it is so, it uses its currently stored data
        // https://stackoverflow.com/questions/29638598/strtok-why-you-have-to-pass-the-null-pointer-in-order-to-get-the-next-token
        array[++i] = strtok(NULL," ");
    }
    
    printf("\n");
    
}