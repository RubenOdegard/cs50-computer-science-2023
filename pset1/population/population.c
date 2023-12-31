#include <cs50.h>
#include <stdio.h>

int startSize; // start size of population
int endSize;   // end size of population
int n = 0;     // amount of years

int main(void)
{
    // TODO: Prompt for start size
    do
    {
        startSize = get_int("Start size: ");
    }
    while (startSize < 9);

    // TODO: Prompt for end size
    do
    {
        endSize = get_int("End size: ");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    while (startSize < endSize)
    {

        // this code will run until startSize reaches the threshhold (because more are born than dying each year, so population will
        // increase

        // each year, n / 3 llamas are born
        int populationIncrease = startSize / 3;
        // each year, n / 4 llamas pass away
        int populationDecrease = startSize / 4;
        // calculate the change of the population
        int populationChange = populationIncrease - populationDecrease;
        // add the populationChange to the startSize
        startSize += populationChange;
        // increment 1 year each loop
        n++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", n);
}
