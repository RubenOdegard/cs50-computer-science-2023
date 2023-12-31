#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{

    // Your program must first ask the user for a message using get_string.
    string message = get_string("Message: ");
    // Your program must then convert the given string into a series of 8-bit binary numbers, one for each character of the string.
    int binary[BITS_IN_BYTE];
    int decimalValue;
    int length = strlen(message);

    for (int i = 0; i < length; i++)
    {

        decimalValue = message[i];
        // we initialize k as 8 -1 because we count from 0. we want to start in the back of the array from right to left.
        // we start by filling the slot for binary[7], decreasing as we go.
        // usual behavior from arrays are right to left and starting with binary[0].
        for (int k = BITS_IN_BYTE - 1; k >= 0; k--)
        {
            binary[k] = decimalValue % 2;
            decimalValue = decimalValue / 2;
        }
        // You can use the provided print_bulb function to print a series of 0s and 1s as a series of yellow and black emoji, which represent on and off light bulbs.
        // Each “byte” of 8 symbols should be printed on its own line when outputted; there should be a \n after the last “byte” of 8 symbols as well.
        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            print_bulb(binary[k]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
