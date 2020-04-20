#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            float grayscale_value = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            image[i][j].rgbtRed = round(grayscale_value);
            image[i][j].rgbtGreen = round(grayscale_value);
            image[i][j].rgbtBlue = round(grayscale_value);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            float sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            float sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            float sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            sepiaRed = sepiaRed > 255 ? 255 : sepiaRed;
            sepiaGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            sepiaBlue = sepiaBlue > 255 ? 255 : sepiaBlue;

            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width / 2; j += 1)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float blur_red, blur_green, blur_blue;
    RGBTRIPLE copy[height][width];

    // make a copy of the image
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    blur_red = (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 4.0;
                    blur_green = (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                  copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 4.0;
                    blur_blue = (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                 copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4.0;
                }

                else if (j == width - 1)
                {
                    blur_red = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 4.0;
                    blur_green = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                  copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 4.0;
                    blur_blue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                 copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 4.0;
                }

                else
                {
                    blur_red = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0;
                    blur_green = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                  copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0;
                    blur_blue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                 copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0;
                }
            }

            else if (i == height - 1)
            {
                if (j == 0)
                {
                    blur_red = (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 4.0;
                    blur_green = (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                  copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 4.0;
                    blur_blue = (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                 copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 4.0;
                }

                else if (j == width - 1)
                {
                    blur_red = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 4.0;
                    blur_green = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                  copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 4.0;
                    blur_blue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                 copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 4.0;
                }

                else
                {
                    blur_red = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 6.0;
                    blur_green = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                  copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 6.0;
                    blur_blue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                 copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 6.0;
                }
            }

            else
            {
                if (j == 0)
                {
                    blur_red = (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0;
                    blur_green = (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                  copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0;
                    blur_blue = (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                 copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0;
                }

                else if (j == width - 1)
                {
                    blur_red = (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                                copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0;
                    blur_green = (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                                  copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0;
                    blur_blue = (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                                 copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0;
                }

                else
                {
                    blur_red = (copy[i][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0;
                    blur_green = (copy[i][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                  copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                  copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0;
                    blur_blue = (copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                 copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                 copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0;
                }
            }

            image[i][j].rgbtRed = round(blur_red);
            image[i][j].rgbtGreen = round(blur_green);
            image[i][j].rgbtBlue = round(blur_blue);
        }
    }

    return;
}
