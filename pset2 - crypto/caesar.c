// PBS @ CS50x
// 24.07.2017
// Implement a program that encrypts messages using Caesar’s cipher

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main( int argc, string argv[] )
{
    
    if( ! argv[1] ){
      
      printf("please insert your cypher key\n");
      return 1;
        
    }
    
    (void)argc;
    string input;
    int key = atoi( argv[1] );
    
    if( key < 0 )
    {
        
        printf("non-negative integers only\n");
        return 2;   
        
    }
    
    do{
        
        printf("plaintext: ");
        input = get_string();
        
    }while( input[0] == '\0' );
    
    int alphabetical_index;
    int remain;
    int ascii_start;
    
    printf("ciphertext: ");
    
    for( int i = 0, n = strlen( input ); i < n; i++ )
    {
        
        if( isalpha( input[i] ) )
        {
            
            // know where to start counting
            if( islower( input[i] ) )
                ascii_start = 97;
            else
                ascii_start = 65;
            
            //printf("we have a alpha with ASCCI value of %i ", input[i] );
            
            // calculates alpha index, example: "a" = 65 - 65 = 0
            alphabetical_index = input[i] - ascii_start;
            
            //printf("and alphabetical index of %i \n", alphabetical_index );
            
            // remainder of 26 ( chars ) that is the offset
            remain = ( alphabetical_index + key ) % 26;
            
            //printf("and the remain is %i \n", remain );
            
            // add the offset ( remain ) to ascii_start
            // to get the ascii number of the cyphered char
            printf("%c", ascii_start + remain );
            
        }
        else
        {
            // we have symbol or numeric char
            printf("%c", input[i]);
        }
        
    }
    
    printf("\n");
    
}