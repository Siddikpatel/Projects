#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// Function to count number of letters in a string
int letterCount(string text);
// Function to count number of words in a string
int wordCount(string text);
// Function to count number of sentences in a string
int sentenceCount(string text);

int main(void)
{
    string text = get_string("Text: ");
    // Counting average number of letters per 100 words
    float L = (100 * (float) letterCount(text)) / (float) wordCount(text);
    // Counting average number of sentences per 100 words
    float S = (100 * (float) sentenceCount(text)) / (float) wordCount(text);
    // Counting grade
    float index = 0.0588 * (float) L - 0.296 * (float) S - 15.8;
    // Rounding and printing the appropriate grade
    int grade = round(index);
    for (int i = 1; i <= 16; i++)
    {
        if (grade == i)
        {
            printf("Grade %i\n", i);
        }
    }
    // Checking if grade is less than 1 or greater than 16
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    
}

int letterCount(string text)
{
    int i = 0, count = 0;
    while (text[i] != '\0')
    {
        // Checking if a character is a valid letter or just a symbol and according to that counting it as a letter
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122) || (text[i] >= 48 && text[i] <= 57))
        {
            i++;
            count++;
        }
        else
        {
            i++;
        }
    }
    return count;
}

int wordCount(string text)
{
    int n = strlen(text), count = 0;
    // Counting words by checking space between letters
    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ' || i + 1 == n)
        {
            count++;
        }
    }
    return count;
}

int sentenceCount(string text)
{
    int n = strlen(text), count = 0;
    // Counting sentences by checking fullstop, question mark & exclamation mark
    for (int i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
    }
    return count;
}