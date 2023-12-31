#include <cs50.h>
#include <stdio.h>

int secondDigit(long cardNumber);

int main(void)
{

    long cardNumber = get_long("Number: ");
    int sumSecondDigit = secondDigit(cardNumber);
}

int secondDigit(long cardNumber)
{
    int sum = 0;

    // false by default, as we are starting in the end of the input and want to get each alternate digit. first one is false.
    bool countAlternateDigit = false;

    while (cardNumber > 0)
    {
        if (countAlternateDigit == true)
        {
            // get the last number
            int lastDigit = cardNumber % 10;
            // add the last digit to the sum
            sum = sum + lastDigit;
        }
        // this will make the boolean the opposite of the current value each time it runs in the while loop.
        countAlternateDigit = !countAlternateDigit;
        // remove the last nymber from the cardNumber
        cardNumber = cardNumber / 10;
    }
    return sum;
}