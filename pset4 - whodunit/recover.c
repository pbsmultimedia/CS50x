#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main( int argc, char *argv[] )
{

    (void) argc;

    // get a pointer to the file
    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL) {

        printf("Could not open file.");
        return 1;

    }

    int jpeg_count = 0;
    int bytes_read = 0;

    // MUST de declared first than the outfile pointer..!
    // or else weird stuff will happen with the bytes..
    uint8_t buffer[512];

    FILE* outfile = NULL;

    char name[4];

    while (1)
    {
        // store bytes read to write only those bytes!
        bytes_read = fread(&buffer, 1, 512, inptr);

        //printf("-------- read %i bytes --------\n", bytes_read);

        if (
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            ( buffer[3] & 0xf0 ) == 0xe0
        ){

            if ( outfile != NULL )
            {
                fclose( outfile );
            }

            sprintf(name, "%03d.jpg", jpeg_count);
            outfile = fopen(name, "w");

            fwrite(&buffer, 1, bytes_read, outfile);
            jpeg_count++;

        }
        else if (outfile != NULL  )
        {
            fwrite(&buffer, 1, bytes_read, outfile);
        }

        // close files and end program if end of file is reached
        if (feof(inptr))
        {

            fclose(inptr);
            if (outfile != NULL)
            {
                fclose(outfile);
            }
            return 0;
        }

    } // end while

    fclose(inptr);

    return 0;

}