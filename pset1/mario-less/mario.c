#include <cs50.h>
#include <stdio.h>

// the pyramid has a max height of 8, so we need a height variable to control this height.
int height;

int main(void)
{

    // user input, height must be between 1 and 8.
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // create each row one by one, with 1 space more each height.
    // "row <= height" makes sure that the loop will run as long as the row is less than or equal to the height input.
    // row will increment with 1 each time the loop goes around.
    for (int row = 1; row <= height; row++)
    {

        // printing spaces before hash symbols.
        // space = user input height - the current row (for example inout of 8 will make the first row have 7 spaces and our next
        // for loop prints 1 hash on the firs row). the loop will continue as long as space is greater than 0. the amounth of spaces
        // decreaments with 1 each loop.
        for (int space = height - row; space > 0; space--)
        {
            printf(" ");
        }

        // printing hash symbols
        // "hashSymbol <= row" makes sure that the loop will run as long as the row is less than or equal to the current row.
        // for each row, the hashSymbol increments with 1.
        for (int hashSymbol = 1; hashSymbol <= row; hashSymbol++)
        {
            printf("#");
        }
        // new line after row loop
        printf("\n");
    }
}