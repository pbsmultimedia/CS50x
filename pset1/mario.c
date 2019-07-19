// Implement a program that prints out a double half-pyramid of a specified height, per the below.
#include <stdio.h>
#include <cs50.h>

void draw_pyramid_row( int height, int loop );

int main(void)
{
    
    printf("Type pyramid height: ");

    int height;

    // ask for valid input while input is invalid
    do
    {
        
        height = get_int();
        
        if( height < 0 || height > 23  )
            printf("height: %i is invalid, insert a positive integer, smaller than 24\n", height);
        
    }
    
    while( height < 0 || height > 23 );
    
    for( int i = 0; i < height; i++ )
    {
        
        draw_pyramid_row( height, i );
        
        // new line after each row
        printf("\n");
        
    }
    
}    

void draw_pyramid_row( int height, int loop )
{

    for( int i = 0; i < height; i++ )
    {

        // left side
        // calculate the number of white spaces
        // white spaces = each loop is the height minus the current loop 
        if( i < height - ( loop + 1 ) )
            printf(" ");
        else
            printf("#");

    }

    // separator
    printf("  ");

    // right side
    // make # as many as the current loop
    for( int i = 0; i <= loop; i++ )
    {
        printf("#");

    }

}