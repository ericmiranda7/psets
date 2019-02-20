// Resizes a bitmap file by n

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

// Initialise write function
void writepix(int, int, FILE *, FILE *);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize scale infile outfile\n");
        return 1;
    }

    // remember n, filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

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

    // Edit BITMAPINFOHEADER
    bi.biWidth *= n;
    bi.biHeight *= n;

    // Determine padding of new & original file
    int outpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int inpadding = (4 - (bi.biWidth/n * sizeof(RGBTRIPLE)) % 4) % 4;

    // Outfile biSizeImage
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + outpadding) * abs(bi.biHeight);

    // Edit BITMAPFILEHEADER
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int row = 0, biHeight = abs(bi.biHeight/n); row < biHeight; row++)
    {
        for (int v = 0; v < n - 1; v++)
        {
            // Call write function
            writepix(n, bi.biWidth, inptr, outptr);

            // Send cursor back
            fseek(inptr, -(sizeof(RGBTRIPLE) * (bi.biWidth/n) + inpadding ), SEEK_CUR);
        }
        writepix(n, bi.biWidth, inptr, outptr);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

void writepix(int n, int bw, FILE *inptr, FILE *outptr)
{
    // Determine infile & outfile padding
    int inpadding = (4 - (bw/n * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpadding = (4 - (bw * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over pixels in scanline
    for (int pix = 0, w = (bw/n); pix < w; pix++)
    {
        // Storage for each pixel
        RGBTRIPLE triple;

        // read RGB triple from infile
        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

        // write RGB triple to outfile n times
        for (int i = 0; i < n; i++)
        {
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
    }
    // skip over infile padding, if any
    fseek(inptr, inpadding, SEEK_CUR);

    // Add padding to outfile
    for (int k = 0; k < outpadding; k++)
    {
        fputc(0x00, outptr);
    }
}