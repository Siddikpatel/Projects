#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Exact 2 conditions are required so validating arguments here
    if (argc == 2)
    {
        // Checking if 2nd argument is valid non-negative integer of 26 distinct letters or not
        if (strlen(argv[1]) == 26)
        {
            for (int i = 0; argv[1][i] != '\0'; i++)
            {
                // Checking if two letters in key are different or not
                for (int j = 1; j <= 26; j++)
                {
                    if (j == i)
                    {
                        continue;
                    }
                    else if (argv[1][i] == argv[1][j])
                    {
                        // 2 letters in key are same so exiting the program
                        printf("Usage: %s key\n", argv[0]);
                        return 1;
                    }
                }
                // Checking if ith letter is alphabet or not
                if (!isalpha(argv[1][i]))
                {
                    printf("Usage: %s key\n", argv[0]);
                    return 1;
                }
            }
        }
        // Arguments are not exactly 2 so exiting from program
        else
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    // Getting input from user
    string plainText = get_string("plaintext: ");
    string cipherText = plainText;
    // Encrypting full input letter by letter
    for (int i = 0; plainText[i] != '\0'; i++)
    {
        if (isupper(plainText[i]))
        {
            // Encrypting ith letter by converting argv to uppercase
            // Where argv is the character that is 65 places behind plaintext
            // We are considering position of corresponding letter in argv, not it's ascii code
            // Eg: if plaintext is letter 65 then ciphertext is argv's 65-65 = 0th letter in uppercase
            cipherText[i] = toupper(argv[1][plainText[i] - 65]);
        }
        else if (islower(plainText[i]))
        {
            // Same logic but plaintext is lowercase so ciphertext is argv's plaintext-97-
            // In lowercase
            cipherText[i] = tolower(argv[1][plainText[i] - 97]);
        }
        else
        {
            // Plaintext is not an alphabet so printing ciphertext same as plaintext
            cipherText[i] = plainText[i];
        }
    }
    printf("ciphertext: %s\n", cipherText);
}