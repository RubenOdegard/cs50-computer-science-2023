#include "helpers.h"

// colorize image
void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // first we loop over the height of the image
    for (int imageHeight = 0; imageHeight < height; imageHeight++)
    {
        // for each pixel in height we loop over, we also want to loop over the width of the row in the image
        // this way we loop through the whole width of the image, each time we loop througb a new height pixel.
        for (int imageWidth = 0; imageWidth < width; imageWidth++)
        {
            // hint: If we were to save the first pixel as RGBTRIPLE pixel = image[0][0]
            // we could then access each of the individual colors of pixel as pixel.rgbtBlue, pixel.rgbtGreen, and pixel.rgbtRed.
            // hexidecimal for black = 0x00 (0 red, 0 green and 0 blue)
            if (image[imageHeight][imageWidth].rgbtRed == 0x00 && image[imageHeight][imageWidth].rgbtGreen == 0x00 &&
                image[imageHeight][imageWidth].rgbtBlue == 0x00)
            {
                image[imageHeight][imageWidth].rgbtBlue = 0xdd;
            }
        }
    }
}
