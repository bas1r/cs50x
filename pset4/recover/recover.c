#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check for one command line
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // Remember filenames
    char *inFile = argv[1];

    // Open input file
    FILE *inptr = fopen(inFile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Invalid file %s.\n", inFile);
        return 1;
    }

    // create buffer
    BYTE *buffer = malloc(BLOCK_SIZE);

    // set counter for filename
    int imageCount = 0;

    // create filename arrays
    char fileName[8];
    FILE *img = NULL;

    // set flag
    bool flag = false;

    // read the file
    while (fread(buffer, BLOCK_SIZE, sizeof(BYTE), inptr) == 1)
    {
        // check the header of the jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close current jpeg
            if (flag == true) //
            {
                fclose(img);
            }
            // condition for found jpeg
            else
            {
                flag = true;
            }

            sprintf(fileName, "%03i.jpg", imageCount);
            img = fopen(fileName, "w");
            imageCount++;
        }

        if (flag == true)
        {
            fwrite(buffer, BLOCK_SIZE, sizeof(BYTE), img);
        }
    }

    // close all files
    fclose(inptr);
    fclose(img);

    // freeing the memory
    free(buffer);

    return 0;
}