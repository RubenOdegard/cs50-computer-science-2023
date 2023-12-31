#include <cs50.h>
#include <stdio.h>

int height = 0;

int main(void)
{

    // input, min: 1 and  max: 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // loops through and create rows as long as the row is lower og equal to the height input
    for (int row = 1; row <= height; row++)
    {
        // left space of pyramid
        for (int space = height - row; space > 0; space--)
        {
            printf(" ");
        }

        // actual pyramid
        for (int hashSymbol = 1; hashSymbol <= row; hashSymbol++)
        {
            printf("#");
        }

        // gap between pyramids
        printf("  ");

        // right side of pyramid (without spaces)
        for (int hashSymbol = 1; hashSymbol <= row; hashSymbol++)
        {
            printf("#");
        }

        printf("\n");
    }
}