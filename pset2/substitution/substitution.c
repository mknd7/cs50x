#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getLetterNumber(char letter)
{
    if (islower(letter))
    {
        return letter - 97;
    }
    else
    {
        return letter - 65;
    }
}

int verifyKey(string key)
{
    // Check if length is exactly 26 chars
    if (strlen(key) != 26)
    {
        return 0;
    }

    // Initializing array to track all letters in the alphabet
    int charsPresent[26];
    for (int i = 0; i < 26; i += 1)
    {
        charsPresent[i] = 0;
    }

    // Check for digits if any, update alphabet array
    for (int i = 0; i < 26; i += 1)
    {
        if (!isalpha(key[i]))
        {
            return 0;
        }
        charsPresent[getLetterNumber(key[i])] = 1;
    }

    // Check if all letters of the alphabet are present before proceeding
    for (int i = 0; i < 26; i += 1)
    {
        if (!charsPresent[i])
        {
            return 0;
        }
    }

    // Key has been verified
    return 1;
}

string plainToCipher(string plaintext, string key)
{
    string ciphertext = plaintext;

    for (int i = 0; i < strlen(plaintext); i += 1)
    {
        if (isalpha(plaintext[i]))
        {
            int letterNumber = getLetterNumber(plaintext[i]);
            if (islower(plaintext[i]))
            {
                ciphertext[i] = tolower(key[letterNumber]);
            }
            else
            {
                ciphertext[i] = toupper(key[letterNumber]);
            }
        }
        ciphertext[i] = plaintext[i];
    }

    return ciphertext;
}

int main(int argc, string argv[])
{
    // No cli argument or more than one argument
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./caesar key");
        printf("\n");
        return 1;
    }

    if (!verifyKey(argv[1]))
    {
        printf("Key must\n");
        printf("- have exactly 26 characters\n");
        printf("- not contain numbers\n");
        printf("- contain all letters of the alphabet\n");
        printf("- each letter may be present only once\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    string key = argv[1];

    string ciphertext = plainToCipher(plaintext, key);
    printf("ciphertext: %s", ciphertext);
    printf("\n");

    return 0;
}