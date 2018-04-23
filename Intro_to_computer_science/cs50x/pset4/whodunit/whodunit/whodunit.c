#include <stdio.h>
#include <cs50.h>

#include "../bmp.h"

// Answer reads: It was colonel mustard with the candlestick in the library.

// full color
BYTE full = 0xff;


// prototypes
bool is_red(RGBTRIPLE* pixel);
bool is_white(RGBTRIPLE* pixel);
void make_red(RGBTRIPLE* pixel);
void make_white(RGBTRIPLE* pixel);


int main(int argc, string argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: infile outfile \n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];
    char* outfile = argv[2];


    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // if red pixel, write white pixel to outfile
            if (is_red(&triple))
            {
                make_white(&triple);
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            // if not red or white, write red to outfile
            else if (!is_white(&triple))
            {
                make_red(&triple);
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            // write everything else to outfile unmodified.
            else
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

bool is_red(RGBTRIPLE* pixel)
{
    if (pixel->rgbtBlue == 0x00 && pixel->rgbtGreen == 0x00 &&
        pixel->rgbtRed == full)
        return true;
    return false;
}

bool is_white(RGBTRIPLE* pixel)
{
    if (pixel->rgbtBlue == full && pixel->rgbtGreen == full &&
        pixel->rgbtRed == full)
        return true;
    return false;
}

void make_red(RGBTRIPLE* pixel)
{
    pixel->rgbtBlue = 0x00;
    pixel->rgbtGreen = 0x00;
    pixel->rgbtRed = full;
}

void make_white(RGBTRIPLE* pixel)
{
    pixel->rgbtBlue = full;
    pixel->rgbtGreen = full;
    pixel->rgbtRed = full;
}
