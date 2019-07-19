/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// solution board
int solution_board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        // TO-DO: uncomment this
        //clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // TODO
    //printf("\nInitializes the game's board with tiles numbered 1 through d*d - 1\n");
    
    /*
    // solution for 3 x 3:
    3 4 1 2 5 8 7 6 4 1 2
    5 8 7 6 4 1 2 4 1 2 3
    5 4 7 6 1 2 3 7 4 8 6
    4 8 5 7 8 5 6 4 5 6 7 
    8 6 5 4 7 8
    */
    
    int counter = d * d -1;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            
            //printf("board is: %i\n", board[i][j]);
            
            //printf("j is: %i\n", j );
            //printf("i is: %i\n", i );
            
            board[i][j] = counter;
            
            if( counter > 0 )
                solution_board[i][j] = d * d - counter;
            else
                solution_board[i][j] = 0;
    
            counter --;
            
        }
        
    }
    
    // for the game be winnable
    // if d is even there must be a swap
    // something with "parity of the permutation"..
    if ((d % 2) == 0)
    {
        // switch numbers 2 and 1
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    //printf("\n");
    
    int counter = 0;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            
            //fprintf(file, "%i", board[i][j]);
            
            //printf("board is: %i\n", board[i][j]);
            
            //printf("j is: %i\n", j );
            //printf("i is: %i\n", i );
            
            if( counter == d  )
            {
                counter = 0;
                printf( "\n" );
            }
            //else    
                
                counter++;
            
            if( board[i][j] > 0 )    
                printf("%2i ", board[i][j]);
            else
                printf(" - ");
        
            //counter --;
            
        }
        //fprintf(file, "\n");
        
    }    
    
    printf("\n\n");
    
    //exit(1);
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    
    //printf("\n check if tile %i can make legal move ( if empty tile is to the left, right, top or bottom.. )", tile);
    
    // get another names..
    int tile_x = -1;
    int tile_y = -1;
    int empty_tile_x = -1;
    int empty_tile_y = -1;
    bool status = false;
    
    // loop to compare values and get keys
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // get the keys
            // tile
            if( board[i][j] == tile )
            {
                //printf("key of tile is [%i][%i]\n", i, j);
                tile_x = j;
                tile_y = i;
            }
            // empty tile
            else if( board[i][j] == 0 )
            {
                //printf("key of empty tile is [%i][%i]\n", i, j);
                empty_tile_x = j;
                empty_tile_y = i;
            }
                
                
            //printf("tile_x is %i and empty_tile_x is %i \n", tile_x, empty_tile_x);    
            // do the math
            // same line [j] + or  - 1
            // line above / bellow  [i] + or - d
            
            // should only be done when both are defined..
            if( tile_x > -1 && empty_tile_x > -1 )
            {
                
                //printf("step one\n");
                
                // match on row
                if( ( ( tile_x - 1 == empty_tile_x ) || ( tile_x + 1 == empty_tile_x ) ) && ( tile_y == empty_tile_y )  )
                {
                    
                    board[empty_tile_y][empty_tile_x] = tile;
                    board[tile_y][tile_x] = 0;
                    // swap
                    //return true;
                    //exit(1);
                    status = true;
                    //printf("status is %d\n", status);
                    break;
                }
                // match on col
                else if( ( ( tile_y - 1 == empty_tile_y ) || ( tile_y + 1 == empty_tile_y ) ) && ( tile_x == empty_tile_x )  )
                {
                    
                    board[empty_tile_y][empty_tile_x] = tile;
                    board[tile_y][tile_x] = 0;
                    // swap
                    //return true;
                    //exit(1);
                    status = true;
                    //printf("status is %d\n", status);
                    break;
                }
                
            }
                    
        }
        
    }
    
    return status;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    
    // checking if won - array is 1, 2, ..
    //printf("checking if won and D is %i\n", d);
    
    int dif = 0;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            //printf("original: %i \n", board[i][j]);
            //printf("solution: %i \n", solution_board[i][j]);
            if( board[i][j] != solution_board[i][j] )
                dif = 1;
        }
        
    }    
    
    if( dif == 1 )
        return false;
    else
        return true;
}