// PBS @ CS50x
// 13.07.2017
// Implement a program that determines whether a provided credit card number is valid according to Luhn’s algorithm.

#include <stdio.h>
#include <cs50.h>

void draw_pyramid_row( int height, int loop );

int main(void)
{
    
    printf("Type card number: ");
    
    long long cc_number;
    //long long cc_number = 378282246310005;
    
    // ask for valid cc
    do
    {
        
        cc_number = get_long_long();
        
    }
    
    while( cc_number < 1  );
    
    long long cc_number_divided;
    
    int every_other_second = 0;
    int every_other_second_result = 0;
    int other_digits_result = 0;
    
    // divide the cc number by 100, until it´s greater than zero 
    for( cc_number_divided = cc_number; cc_number_divided > 0; cc_number_divided /= 100 )
    {
        
        //printf( "%lld \n", cc_number_divided );
        
        // excludes the last digit, then gets the remainder
        every_other_second = cc_number_divided / 10 % 10;
        // gets the last two digits
        //printf("gets the remainder: %i", every_other_second );
        
        int x = every_other_second * 2;
        
        // add the result digits together
        // trick to add two digits
        if( x > 9 )
        {
            /*
            printf(" is > 9");
            printf("\nfirst digit is: %i", x / 10 );
            printf("\nremainder is: %i", x % 10 );
            */
            
            // first digit
            every_other_second_result += x / 10;
            
            // second digit
            every_other_second_result += x % 10;
            
        }
        else{
            
            //printf(" is < 9");
            every_other_second_result += x;
            
        }
        
        other_digits_result += cc_number_divided % 10;
        
    }
    
    // checksum passes
    if( ( every_other_second_result + other_digits_result ) % 10 == 0 )
    {
        
        if( ( cc_number >= 340000000000000 && cc_number < 350000000000000 ) || ( cc_number >= 370000000000000 && cc_number < 380000000000000 ) )
            printf("AMEX\n");
        else if( cc_number >= 5100000000000000 && cc_number < 5600000000000000 )    
            printf("MASTERCARD\n");
        else if( ( cc_number >= 4000000000000 && cc_number < 5000000000000 ) || ( cc_number >= 4000000000000000 && cc_number < 5000000000000000 ) )
            printf("VISA\n");
        else    
            printf("INVALID\n");
            
    }
    // fails    
    else
        printf("INVALID\n");
        
}