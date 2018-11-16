#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Name of memory card\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char outfile[8];

    //open infile
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    int counter = 0;
    uint8_t data[512];
    FILE *img = NULL;

    do {

        //check jpg header
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && (data[3] & 0xf0) == 0xe0)
        {
            //if img is empty, name outfile and open it
            if (img == NULL)
            {
                sprintf(outfile,"%03i.jpg",counter);
                img = fopen(outfile, "w");
            }

            //if img is not empty, close outfile and open a new one
            else if(img != NULL)
            {
                counter++;
                fclose(img);

                sprintf(outfile,"%03i.jpg",counter);
                img = fopen(outfile, "w");
            }
        }

        //if outfile is open, write
        if (counter > 0)
        {
            fwrite(&data, 512, 1, img);
        }
    }
    while(fread(&data, 512, 1, inptr) == 1);

    fclose(inptr);

    //close img
    if (img != NULL)
    {
        fclose(img);
    }
}