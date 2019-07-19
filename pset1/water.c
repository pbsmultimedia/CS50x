// Implement a program that reports a user’s water usage, converting minutes spent in the shower to bottles of drinking water.

#include <stdio.h>
#include <cs50.h>

int main(void)
{

    // shower spits out 1.5 gallons of water per minute
    // A gallon, meanwhile, is 128 ounces
    // A typical bottle of water (that you might have for a drink, not a shower), meanwhile, might be 16 ounces
    // So taking a 1-minute shower is akin to using 192 ÷ 16 = 12 bottles of water
    // 192 ÷ 16 = 12 ( ( 128 ounces * 1.5 gallons by minute ) / 16 ounces of the bottle )
    
    // 1 minute - 1.5 gallons
    // 1 gallon - 128 ounces
    // 1 bottle - 16 ounces

    printf("Minutes: ");
    int minutes = get_int();
    
    int result = 128 * ( 1.5 * minutes ) / 16;
    
    printf("Bottles is %i", result );
    
}    