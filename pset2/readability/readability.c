#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Coleman-Liau formula
float CL_Index(float L, float S);

// function to count all letters
int count_letters(string text);

// function to count all words
int calc_words(string text);

// function to calculate sentences
int calc_sentences(string text);

int main(void)
{

    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = calc_words(text);
    int sentences = calc_sentences(text);

    /*
    printf("%d letters \n", letters);
    printf("%d words \n", words);
    printf("%d sentences \n", sentences);
    printf("\n");
    */

    float averageLetters = (float) letters / words * 100.0;
    float averageSentence = (float) sentences / words * 100.0;

    /*
    printf("Average letters: %.2f\n", averageLetters);
    printf("Average sentence: %.2f\n", averageSentence);
    printf("\n");
    */

    float index = CL_Index(averageLetters, averageSentence);

    // if index is greater than 16, display Grade16+, otherwise display grade + index.
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %0.f\n", (float) round(index));
    }
}

// I take the formula provided and extract it to its own function, so i can reuse it at any time.
// L is the average number of letters per 100 words, S is the average sentences per 100 words of text.
float CL_Index(float L, float S)
{
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}

// need to find total letters, words and sentences.
// split by " " counts as words
// split by "period, exclamation point, or question mark" indicates the end of a sentence

// function to count all letters in a string
int count_letters(string text)
{
    int length = strlen(text);
    int count = 0;

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// function to count all words in a string
int calc_words(string text)
{
    // here i want to use the isspace() from <ctype.h> to determine if we are looping through a character or a space between words.
    // i will use a boolean to trigger true or false if we are looping on a character or a space.

    int length = strlen(text);
    int count = 0;
    bool isInsideWord = false;

    for (int i = 0; i < length; i++)
    {
        // check if we are looping on a space, if so we set isInsideWord to false.
        if (isspace(text[i]))
        {
            isInsideWord = false;
        }
        else
        {
            // If this condition is true, we have landed on a space, so we set isInsideWord to true and add to the count.
            // each time we encounter a space, we have one word added to count.
            if (!isInsideWord)
            {
                isInsideWord = true;
                count++;
            }
        }
    }
    return count;
}

// function to calculate sentences in a string
int calc_sentences(string text)
{
    // we reuse a lot of the code from calculating words, but now split by period, exclamation point or question mark.
    // that way, each time we encounter one of thes three, we can add count by 1.

    int length = strlen(text);
    int count = 0;
    bool isInsideSentence = false;

    for (int i = 0; i < length; i++)
    {

        // variable for the current character being looped through
        char current = text[i];

        // check to see if we hit any of the markers that signifies a sentence in our case
        // if we hit one of these, we can add to count because we have left a sentence and entering a new one.
        if (current == '.' || current == '!' || current == '?')
        {
            isInsideSentence = false;
            count++;
        }
        else
        {
            // if this condition renders, we are checking to see if we are in fact inside a sentence
            if (!isInsideSentence && isalpha(current))
            {
                isInsideSentence = true;
            }
        }
    }
    return count;
}
