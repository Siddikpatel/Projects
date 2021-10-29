#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Defining BYTE type
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("AN \"UNKNOWN\" ERROR OCCURED!\n");
        return 1;
    }
    // Opening file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        return 2;
    }
    // Image file
    FILE *image;
    // Initializing 512 block
    BYTE buffer[512];
    // File name
    char fname[8];
    // Counting files
    int count = 0;
    // Crisp
    while (fread(buffer, sizeof(buffer), 1, card) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count > 0)
            {
                // Close file
                fclose(image);
                // Change file name
                sprintf(fname, "%03d.jpg", count);
                // Open file to write
                image = fopen(fname, "w");
                // Write data
                fwrite(buffer, sizeof(buffer), 1, image);
                count++;
            }
            if (count == 0)
            {
                // Change file name
                sprintf(fname, "%03d.jpg", count);
                // Open file to write
                image = fopen(fname, "w");
                // Write data
                fwrite(buffer, sizeof(buffer), 1, image);
                count++;
            }
        }
        else if (count > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, image);
        }
    }
    fclose(image);
    fclose(card);
}