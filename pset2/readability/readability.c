#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text;
    text = get_string("Text: ");

    float letters, words, sentences;
    letters = words = sentences = 0;

    for (int i = 0; i < strlen(text); i += 1)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters += 1;
        }
        else if (text[i] == ' ')
        {
            words += 1;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences += 1;
        }
    }

    // Count the last word
    if (strlen(text) > 2)
    {
        words += 1;
    }

    float avgLettersPercent = letters / words * 100;
    float avgSentencesPercent = sentences / words * 100;

    float preciseIndex = 0.0588 * avgLettersPercent - 0.296 * avgSentencesPercent - 15.8;
    int clIndex = (int) round(preciseIndex);

    if (clIndex > 16)
    {
        printf("Grade 16+");
    }
    else if (clIndex < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", clIndex);
    }

    printf("\n");
    return 0;
}