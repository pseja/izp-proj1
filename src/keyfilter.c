#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 101 // 101, because the length of line is 100 but +1 for '\0'
#define MAX_UNIQUE_CHARS 69 // ascii chars from 32 to 126 without small letters

int calculateInputIndex(char c)
{
    if (c >= 32 && c <= 96)
    {
        return c - 32;
    }
    else if (c >= 123 && c <= 126)
    {
        return c - 58;
    }
    return EXIT_FAILURE;
}

int main(int argc, char *argv[])
{
    char *input = argv[1];
    char address[MAX_LINE_LENGTH];
    char possibleChars[MAX_UNIQUE_CHARS];

    // Initializing array with '\0' to later input letters
    for (int i = 0; i < MAX_UNIQUE_CHARS; i++)
        possibleChars[i] = '\0';

    char possibleString[MAX_LINE_LENGTH];
    int found = 0;

    // No argument passed edge case handling
    if (argc < 2)
        input = "";

    // Loads lines to address variable until end of file is reached 
    while (fgets(address, MAX_LINE_LENGTH, stdin) != NULL)
    {
        int i;
        for (i = 0; i < (int)strlen(input); i++)
        {
            // If non matching character was found, break
            if (toupper(input[i]) != toupper(address[i]))
            {
                break;
            }
        }

        // Check if for loop matched the correct string with input
        if (i == (int)strlen(input))
        {
            // Save the first thing that gets passed into possibleChars,
            // for when that thing is the only one passed there i know
            // what is the whole address
            if (found == 0)
                strcat(possibleString, address);

            found++;
            // Calculate where to put the current character
            possibleChars[calculateInputIndex(toupper(address[i]))] = toupper(address[i]);
        }
    }

    if (found == 0)
    {
        printf("Not found\n");
    }
    else if (found == 1)
    {
        printf("Found: ");
        for (int i = 0; i < MAX_LINE_LENGTH; i++)
            printf("%c", toupper(possibleString[i]));
    }
    else
    {
        printf("Enable: ");
        for (int i = 0; i < MAX_UNIQUE_CHARS; i++)
        {
            if (possibleChars[i] != '\0')
                printf("%c", possibleChars[i]);
        }
        printf("\n");
    }
    return 0;
}