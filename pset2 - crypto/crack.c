#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <crypt.h>

// static const..?
static const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
//static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
int total_loops = 0;

// count from zero
//static const int alphabet_size = sizeof(alphabet) - 1;
int alphabet_size = sizeof(alphabet) - 1;

string original_hash;

// * means a pointer to a byte that holds the value
void brute_force(char * str, int index, int digits)
{
    int i;
    // array with 2 elements
    //char salt[2];
    string salt = "50";
    for (i = 0; i < alphabet_size; ++i)
    {
        
        //printf("--- index: %i --- \n", index);
        //printf("--- i: %i --- \n", i);
        
        //if( index == 3 ) exit(0);
        
        // assign the current alphabeth letter   
        str[index] = alphabet[i];
        
        //printf("--- str: %s --- \n", str);
        
        //printf("--- str[x]: %c --- \n", str[index]);
        
        //printf("--- str[0]: %c --- \n", str[0]);

        // if current digit equal total digits - 1
        // loops thru each one, and steps to the next char
        if (index == digits - 1)
        {
            total_loops++;
            // total passwords = ( alphabet length * digits ) + alphabet length ^digits
            // abcdef - 2 digits
            // total passwords = ( 6 * 1 ) + 6 * 0 + ( 6 * 2 ) + 6 * 6
            //printf("--- total_loops: %i --- \n", total_loops);
            
            // assign the two first letters
            /*
            salt[0] = str[0];
            salt[1] = str[1];
            */
            
            //printf("--- str[x]: %c --- \n", str[0]);
            
            string hash = crypt( str, salt);
            //string hash = crypt( str, "AA");
            //printf("hash is: %s", hash );
            
            int res =  strcmp( original_hash, hash );
            
            //printf(" \n --- res is %i --- \n", res);
    
            if( res == 0 )
            {
                // Z: 50R.6FuTGui8U
                // C: 503RHmlyy2lZE
                // abc: 50PaJ4.RO0YUo - does not work..?
                // ab: 50kiZhZaSRp0E
                //printf("we got something!");
                printf("computed password is: %s for hash: %s \n", str, original_hash);
                //printf("%s hash does match %s", original_hash, hash);
                //return; 
                //break;
                exit(0);
                
            }
        }
        else
        {
            // recursive
            // moves to the next digit
            //printf("moving to the next digit %i \n", index + 1);
            brute_force(str, index + 1, digits);
        }
    }
    
    //return 0;
    
}


// main at the end is more simple..
int main(void)
{
    
    //brute_sequential( 4 );
    
    // rofl: 50fkUxYHbnXGw
    // the salt is passed as 2nd argument 
    // and stays as the first two chars of the hash
    /*
    //string hash = crypt("rofl", "50");
    string hash = crypt("ab", "50");
    printf("calculated hash is: %s \n", hash);
    //printf("original hash is: 50fkUxYHbnXGw \n");
    return 0;
    */
    // ask for hash
    
    //string hash;
    
    /*
    do{
        
        original_hash = get_string();
        
    // "" does not work, only ''    
    }while( original_hash[0] == '\0' );
    */
    
    original_hash = get_string();
    
    if( original_hash[0] == '\0' )
    {
        printf("usage ./crack hash\n");
        return 1;
    }
    
    int digits = 4;
    
    //printf("digits: %i\n", digits);
    
    // var that holds the current string
    // ask for 5 bytes of memory
    char * str = malloc(digits + 1); // 0 1 2 3 \0
    int i;

    // loop while i <= digits
    for (i = 1; i <= digits; ++i)
    {
        // ...
        // brute_force( str, index, digits );
        // if found exits the program
        brute_force(str, 0, i);
    }

    // if not found..
    printf("no matching hash was found.");

    // clear memory
    free(str);    
    
}