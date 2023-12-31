#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
// 26 char array, starts at 0 and end at 25 (full english alphabet)
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// my function to compute the score which the users input.
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // (we also need to print something for the case of a tie)

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    // Goal is to take the char input and subscract the value for "a" or "A" so that we get a corresponding value to the POINTS[]
    // array in terms of scoring. uppercase A is 65, 65 - 65 = 0, which gives a point for 1 from the POINTS[] array.

    // create score int
    // loop over each character in the word
    // check if the score is lowercase or uppercase
    // subscract the ascii character value -** for lowercase and -65 for uppercase.

    int score = 0;

    // we use strlen(arg) to get the totalt length of the word, and loop through each character
    for (int i = 0; i < strlen(word); i++)
    {
        // check if the character currently in loop is uppercase, if so we subscract the ascii value.
        // for example, if A is input, 65 - 65 = 0, which corresponds to 0 in the array with a point of 1.
        // if a is input, 97 - 97 = 0, which corresponds equally to 0 in the array, and with a point of 1.
        // this goes on for every character and gives it a place and a point from the POINTS[] array.
        if (isupper(word[i]))
        {
            // uppercase A is equal to 65 in ascii
            // we pick the score based on the corresponding value of the character being in the loop
            score = score + POINTS[word[i] - 65];
        }
        else if (islower(word[i]))
        {
            // lowercase a is equal to 97 in ascii
            score = score + POINTS[word[i] - 97];
        }
    }
    return score;
}
