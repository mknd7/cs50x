#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isStringNumber(string str)
{
    for (int i = 0; i < strlen(str); i += 1)
    {
        if (!isdigit(str[i]))
        {
            return 1;
        }
    }
    return 0;
}

string plainToCipher(string plaintext, int key)
{
    string ciphertext = plaintext;

    for (int i = 0; i < strlen(plaintext); i += 1)
    {
        if (isalpha(plaintext[i]))
        {
            char cipherChar = plaintext[i] + key;
            if (!isalpha(cipherChar))
            {
                cipherChar -= 26;
            }
            ciphertext[i] = cipherChar;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    return ciphertext;
}

int main(int argc, string argv[])
{
    // No cli argument or more than one argument
    // Also checks if string is composed of only numbers
    if ((argc < 2 || argc > 2) || isStringNumber(argv[1]) != 0)
    {
        printf("Usage: ./caesar key");
        printf("\n");
        return 1;
    }

    int key = atoi(argv[1]);
    key = key % 26;

    string plaintext = get_string("plaintext: ");
    string ciphertext = plainToCipher(plaintext, key);

    printf("ciphertext: %s", ciphertext);
    printf("\n");
    return 0;
}