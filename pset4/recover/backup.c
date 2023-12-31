#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check for the correct number of command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the input file for reading
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *outputFile = NULL;
    int jpgCount = 0;
    char jpgName[8];

    while (fread(buffer, 1, BLOCK_SIZE, inputFile) == BLOCK_SIZE) {
        // Check for the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            // Close the previous output file if one is open
            if (outputFile != NULL) {
                fclose(outputFile);
            }

            // Create a new JPEG file
            sprintf(jpgName, "%03d.jpg", jpgCount);
            outputFile = fopen(jpgName, "w");
            if (outputFile == NULL) {
                fprintf(stderr, "Could not create %s\n", jpgName);
                return 1;
            }
            jpgCount++;
        }

        // Write data to the output file if a JPEG is found
        if (outputFile != NULL) {
            fwrite(buffer, 1, BLOCK_SIZE, outputFile);
        }
    }

    // Close the last output file
    if (outputFile != NULL) {
        fclose(outputFile);
    }

    // Close the input file
    fclose(inputFile);

    return 0;
}
