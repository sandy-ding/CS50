// resize a BMP file
//fseek(inptr, -ibiWidth * sizeof(RGBTRIPLE), SEEK_CUR);
//* sizeof(RGBTRIPLE)!!!

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Uncorrect number\n");
        return 1;
    }

    // remember filenames
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

    int ipadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int ibiWidth = bi.biWidth;
    int ibiHeight = bi.biHeight;

    // write outfile's BITMAPINFOHEADER
    bi.biWidth *= n;
    bi.biHeight *= n;
    int opadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // write outfile's BITMAPFILEHEADER
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + opadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(ibiHeight); i < biHeight; i++)
    {
        for (int h = 0; h < n; h++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < ibiWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int k = 0; k < n; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding of infile
            fseek(inptr, -ibiWidth * sizeof(RGBTRIPLE), SEEK_CUR);

            // then add padding to outfile
            for (int k = 0; k < opadding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        //Move backwards and skip over infile padding
        fseek(inptr, ibiWidth * sizeof(RGBTRIPLE) + ipadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
