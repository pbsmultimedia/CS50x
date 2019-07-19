/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resized factor ( between 1 and 100 ) infile outfile\n");
        return 1;
    }

    // remember filenames
    int resized_factor = atoi( argv[1] );
    char *infile = argv[2];
    char *outfile = argv[3];

    // check resize factor
    if ( ( resized_factor < 1 ) || ( resized_factor > 100 ) )
    {
        fprintf(stderr, "resize factor must be between 1 and 100\n");
        return 1;
    }

    printf("resized by %i infile is %s and outfile is %s \n", resized_factor, infile, outfile);

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    // make a copy to resized
    BITMAPFILEHEADER bf, bf_resized;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_resized = bf;

    // read infile's BITMAPINFOHEADER
    // make a copy to resized
    BITMAPINFOHEADER bi, bi_resized;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_resized = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // resizedd image dimensions - width and height
    bi_resized.biWidth = bi.biWidth * resized_factor;
    bi_resized.biHeight = bi.biHeight * resized_factor;

    // determine padding for scanlines - original and resizedd
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_resized = (4 - (bi_resized.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Determine new image sizes ( with new padding )
    // biSizeImage: The size, in bytes, of the image
    bi_resized.biSizeImage = (bi_resized.biWidth * sizeof(RGBTRIPLE) + padding_resized) * abs(bi_resized.biHeight);
    // new bfsize
    // BFSIZE:
    /*
    fSize = biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
    bfSize = biSizeImage + 54
    // since BITMAPFILEHEADER = 40 and BITMAPINFOHEADER = 14
    */
    // FROM: https://stackoverflow.com/questions/25713117/what-is-the-difference-between-bisizeimage-bisize-and-bfsize
    bf_resized.bfSize = bi_resized.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    // applying the new dimensions
    fwrite(&bf_resized, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_resized, sizeof(BITMAPINFOHEADER), 1, outptr);

    // 1- iterate over infile's scanlines
    // something like RGB
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

        // 2- need something here like a row counter to do a loop
        // to make how many rows as resized_factor
        // reproducing the new resized scanline / row, like RRGGBB x 2 =
        // RRGGBB
        // RRGGBB
        for( int row_counter = 0; row_counter < resized_factor; row_counter ++ )
        {

            // 3- iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {

                // temporary storage - outside the loop
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //printf(" X |");

                /*
                printf("red value is: %i\n", triple.rgbtRed );
                printf("green value is: %i\n", triple.rgbtGreen );
                printf("blue value is: %i\n", triple.rgbtBlue );
                */

                // 4- need something here like a col / pixel counter to do a loop
                // write RGB triple to outfile
                // TO-DO multiply by the factor n to write pixel on the horizontal line
                // like RGB x 2 = RRGGBB
                for( int col_counter = 0; col_counter < resized_factor; col_counter++ )
                {

                    //printf(" X |");
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                } // end 4

                //printf("\n");

            } // end 3

            // Add a new padding
            // if the original image, lets says has 3 pixels row
            // and the resize factor is 2, 3 * 2 = 6
            // which is not a multiple of 4 and a scanline must have 32 bits
            //printf("padding resized is: %i \n", padding_resized);

            for (int l = 0; l < padding_resized; l++)
            {
                //printf(" Y |");
                fputc(0x00, outptr);
            }

            //printf("\n");

            // must continue reading the infile scanline
            // back to the start, setting offset as negative
            // and SEEK_CUR that is the current position of the cursor
            int offset = bi.biWidth * sizeof(RGBTRIPLE);
            offset = -offset;

            //printf( "offset for new line is %ld \n", offset );
            //printf( "offset for new line is %i \n", offset );

            printf( "row counter is %i \n", row_counter );
            printf( "resized factor is %i \n", resized_factor );

            // set the cursor to start of the line
            // using the negative offset defined above
            // do that until is row_counter that starts at 0 and resized_factor which starts at 1
            // therefore needs -1
            if ( row_counter < resized_factor - 1 )
                fseek(inptr, offset, SEEK_CUR);

        } // end 2 - end of row

        // avoid infile padding by skipping it
        // stream − This is the pointer to a FILE object that identifies the stream.
        // offset − This is the number of bytes to offset from whence.
        // whence − This is the position from where offset is added
        // SEEK_CUR	Current position of the file pointer
        fseek(inptr, padding, SEEK_CUR);

        printf("looping thru original scan lines, loop %i \n", i);

    } // end 1 - loop original scanlines

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
