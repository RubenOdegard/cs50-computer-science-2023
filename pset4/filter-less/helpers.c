#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // we loop the height of the image
    for (int i = 0; i < height; i++)
    {
        // looping the whole row on each height pixel
        for (int j = 0; j < width; j++)
        {
            // BMP stores these triples backwards, BGR and not RGB
            // rounded to nearest int by adding + 0.5
            int averageColor = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0 + 0.5);
            image[i][j].rgbtBlue = averageColor;
            image[i][j].rgbtGreen = averageColor;
            image[i][j].rgbtRed = averageColor;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // we loop the height of the image
    for (int i = 0; i < height; i++)
    {
        // looping the whole row on each height pixel
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // fmin() returns the lowest of two inputs, ergo if the sepia calc is greater than 255 we will default to 255 as per the
            // instructions. add + 0.5 to round of to nearest.
            image[i][j].rgbtRed = fmin(255, (int) (.393 * originalRed + .769 * originalGreen + .189 * originalBlue + 0.5));
            image[i][j].rgbtGreen = fmin(255, (int) (.349 * originalRed + .686 * originalGreen + .168 * originalBlue + 0.5));
            image[i][j].rgbtBlue = fmin(255, (int) (.272 * originalRed + .534 * originalGreen + .131 * originalBlue + 0.5));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // define the middle of the row, and loop through until the middle. because we are swapping pixels, we go through the whole
        // row "halfway".
        int middle = width / 2;

        for (int j = 0; j < middle; j++)
        {
            RGBTRIPLE tempPixel;
            int findLast = width - 1 - j;
            tempPixel = image[i][j];
            image[i][j] = image[i][findLast];
            image[i][findLast] = tempPixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //  we need to create a copy of the image into a temp variable, which we then modify and then lastly push back into image[][].
    //  variable to hold the temp image
    RGBTRIPLE tempImage[height][width];

    // // vertical loop.
    for (int i = 0; i < height; i++)
    {
        // horizontal loop
        for (int j = 0; j < width; j++)
        {
            // we are looping over each pixels in every row of the picture and storing in tempImage.
            tempImage[i][j] = image[i][j];
        }
    }

    // this loop runs after we have created the temp image and populates it
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // we need to add up the total sum of each color, initializing the ints for storage.
            int sumOfRed = 0;
            int sumOfGreen = 0;
            int sumOfBlue = 0;
            // and we need a counter to count the actual pixels that is not out of bounds.
            // the average will be the sum of each color divided by the counter.
            float counter = 0.00;

            // we loop over 3 pixels horizontally to create the beginning of our 3x3 grid. -1, 0 and 1.
            for (int xAxis = -1; xAxis < 2; xAxis++)
            {
                // here we loop the vertical portion of the 3x3 grid, -1, 0 and 1 to create the grid.
                for (int yAxis = -1; yAxis < 2; yAxis++)
                {
                    // we now need variables to hold the current position, both in x and y (horizontal and vertical)
                    int currentXPixel;
                    currentXPixel = i + xAxis;

                    int currentYPixel;
                    currentYPixel = j + yAxis;

                    // if the pixel on x-axis is less than 0 or greater than height - 1 (height - 1 is the total height, or end of
                    // array) then we are out of bounds of the picture.
                    if (currentXPixel < 0 || currentXPixel > (height - 1) || currentYPixel < 0 || currentYPixel > (width - 1))
                    {
                        continue;
                    }

                    sumOfRed = sumOfRed + image[currentXPixel][currentYPixel].rgbtRed;
                    sumOfGreen = sumOfGreen + image[currentXPixel][currentYPixel].rgbtGreen;
                    sumOfBlue = sumOfBlue + image[currentXPixel][currentYPixel].rgbtBlue;

                    // we add to counter to keep track of how many valid pixels are in the grid. with the continue function above we
                    // skip the non valid pixels. this means that each time counter increments here, we have looped through a valid
                    // pixel in the 3x3 grid.
                    counter++;
                }
            }

            tempImage[i][j].rgbtRed = round(sumOfRed / counter);
            tempImage[i][j].rgbtGreen = round(sumOfGreen / counter);
            tempImage[i][j].rgbtBlue = round(sumOfBlue / counter);
        }
    }
    // this code will run after the temp image is fully populated above.
    // we loop over the entire image again and copy over the new tempImage[] over to image[].
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tempImage[i][j];
        }
    }
    return;
}
