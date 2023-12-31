#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string arg);
char rotate(char c, int rotateBy);

int main(int argc, string argv[])
{

    // check how many arguments, the only correct input is 2 otherwise we return 1 and an error.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // checks if the input argument is a digit, if not we throw and error and return 1.
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // to convert a string (argv is an array of strings), we use atol() from stdlib.h
    // here we also have to specify that we want the key input, which is argv[1] (because ./caesar is argv[0])
    int key = atol(argv[1]);

    // now we get the plaintext from the user (we've made sure we have correct key from the input)
    // and then we will display "Ciphertext:  ", notice we dont have a "\n" in the printf which makes the next function able to
    // print directly on the same line.
    string plaintext = get_string("Plaintext:  ");
    printf("Ciphertext:  ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
}

// check if string arg (argv[1] is a number, and if the number is equal or greater than 0, and equal or less than 9.
// we use the atol() command to convert the string from the function arg to a number, so that we can use >= and <=.
bool only_digits(string arg)
{
    for (int i = 0; i < strlen(arg); i++)
    {
        if (!isdigit(arg[i]))
        {
            return 0;
        }
    }
    return 1;
}

// rotates input within the 26 characters of the alphabet, char c for the character and rotateBy for the key
char rotate(char c, int rotateBy)
{
    if (isupper(c))
    {
        int result = (c - 'A' + rotateBy) % 26 + 'A';
        return result;
    }
    else if (islower(c))
    {
        int result = (c - 'a' + rotateBy) % 26 + 'a';
        return result;
    }
    else
    {
        int result = c;
        return result;
    }
}
