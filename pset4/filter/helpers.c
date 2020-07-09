#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // on each iterations it change the value of each pixel to an average value.
    // iteration through column
    for (int i = 0; i < height; i++)
    {
        //iteration through rows.
        for (int j = 0; j < width; j++)
        {
            int sum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed);
            int average = sum / 3;
            if (sum - (average * 3) == 2)
            {
                average++;
            }
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // On each iteration its taking each pixel and computing new red,green, and blue values based on the orginal values of the three.
        for (int j = 0; j < width; j++)
        {
            // Algorithm for converting an image to sepia.
            int sepiaRed = (int)((.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue) + .5);
            int sepiaGreen = (int)((.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue) + .5);
            int sepiaBlue = (int)((.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue) + .5);

            // If the result of the formula is a number greater than 255 the maximum value for an 8-bite color value. in that case, the red,gree and blue values should be capped at 255.
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // iterating through column and rows
    RGBTRIPLE imageTemp;
    for (int i = 0;  i < height; i++)
    {
        // swaping pixels on the left side to the right and vice versa.
        int width2 = width;
        for (int j = 0; j < width / 2; j++, width2--)
        {
            imageTemp.rgbtRed = image[i][j].rgbtRed;
            imageTemp.rgbtGreen = image[i][j].rgbtGreen;
            imageTemp.rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width2 - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width2 - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width2 - 1].rgbtBlue;
            image[i][width2 - 1].rgbtRed = imageTemp.rgbtRed;
            image[i][width2 - 1].rgbtGreen = imageTemp.rgbtGreen;
            image[i][width2 - 1].rgbtBlue = imageTemp.rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Storing values
    RGBTRIPLE imageC[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageC[i][j].rgbtRed = image[i][j].rgbtRed;
            imageC[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageC[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    // iterating within rows and columns
    // Adding new values to each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int newHeight = 3;
            int newWidth = 3;
            double sumR = 0, sumG = 0, sumB = 0;
            int averageR = 0, averageG = 0, averageB = 0;
            int startHeight = 0, startWidth = 0;
            if (i == 0 || i == height - 1)
            {
                if (j == 0 || j == width - 1)
                {
                    newHeight = 2;
                    newWidth = 2;
                }
                else
                {
                    newHeight = 2;
                    newWidth = 3;
                }
            }
            else if (j == 0 || j == width - 1)
            {
                newHeight = 3;
                newWidth = 2;
            }
            startHeight = i - 1;
            startWidth = j - 1;
            if (startHeight < 0)
            {
                startHeight = 0;
            }
            if (startWidth < 0)
            {
                startWidth = 0;
            }
            for (int k = startHeight; k < newHeight + startHeight; k++)
            {
                for (int z = startWidth; z < newWidth + startWidth; z++)
                {
                    sumR += imageC[k][z].rgbtRed;
                    sumG += imageC[k][z].rgbtGreen;
                    sumB += imageC[k][z].rgbtBlue;
                }
            }
            // The new value of each pixel is the average of the values of all the pixels
            averageR = (int)((sumR / (newHeight * newWidth)) + .5);
            averageG = (int)((sumG / (newHeight * newWidth)) + .5);
            averageB = (int)((sumB / (newHeight * newWidth)) + .5);
            image[i][j].rgbtRed = averageR;
            image[i][j].rgbtGreen = averageG;
            image[i][j].rgbtBlue = averageB;
        }
    }
    return;
}
