// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // header[] array with unsigned 8 bit int, bytes based on header_size
    uint8_t header[HEADER_SIZE];
    // fread(void *ptr (adress where to read), size_t size (the actual size), size_t nmemb (how many to read at once), FILE *stream
    // (which file to read from)); fread and fwrite now reads the first 44 bytes from the input (HEADER_SIZE) and writes it to our
    // output file.
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // unsigned 2 byte sample int, (8 + 8 bits)
    int16_t buffer;
    // read the sample from the input file
    // &buffer sets the address to where we want to store data in memory
    // sizeof(int16_t) sets the size of what we want to read, in this case we need 2 bytes, 16 bits.
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // factor is the agrument from user input. we multiply the bits accordingly
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
