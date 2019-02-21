#include <stdio.h>
#include <stdlib.h>

void writefile(char *, FILE **, int, unsigned char*);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Correct usage: ./recover filename");
        return 1;
    }

    // Remember filename, create jpg file name, counter for files
    char *memfile = argv[1];
    char jpgname[8];
    int n = 0;

    // Open file
    FILE *memptr = fopen(memfile, "r");

    // File pointer for JPEG
    FILE *jpgfile;
    
    // Check for opening error
    if (memptr == NULL)
    {
        fprintf(stderr, "Could not open file");
        return 2;
    }

    // Create storage
    unsigned char buffer[512];

    // Integer to check if JPEG found
    int ajpg = 0;

    // Read bytes
    while(fread(buffer, 512, 1, memptr) == 1)
    {
        // Check if start of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Check if JPEG currently opened
            if (ajpg == 0) // If no
            {
                // Open and write to a new JPEG file
                writefile(jpgname, &jpgfile, n, buffer);
                // Set JPG as open
                ajpg = 1;
            }
            else // If yes
            {
                fclose(jpgfile);
                // Increment file name
                n++;
                writefile(jpgname, &jpgfile, n, buffer);
            }
        }

        // Check if a JPEG is already opened
        else if (ajpg == 1)
        {
            // Write to it
            fwrite(buffer, 512, 1, jpgfile);
        }
    }
}

void writefile(char *jpgname, FILE **jpgfile, int n, unsigned char *buffer)
{
    sprintf(jpgname, "%03i.jpg", n);
    *jpgfile = fopen(jpgname, "w");
    fwrite(buffer, 512, 1, *jpgfile);
}