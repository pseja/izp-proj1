#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define ALPHABET_LENGTH 26

int main(int argc, char *argv[])
{
    char *input = argv[1];
    char address[MAX_LINE_LENGTH];
    char possibleChars[ALPHABET_LENGTH];
    int possibleCharsInputIndex = 0;
    char possibleString[MAX_LINE_LENGTH];

    if (argc < 2)
        input = "";

    // Loads lines to address variable until end of file is reached 
    while (fgets(address, MAX_LINE_LENGTH, stdin) != NULL)
    {
        int i;
        for (i = 0; i < (int)strlen(input); i++)
        {
            if (toupper(input[i]) != toupper(address[i]))
            {
                break;
            }
        }

        // checking if for loop matched the correct string with input 
        // and the character is not already in the list of possible chars
        char *isCharInArray = strchr(possibleChars, toupper(address[i]));
        if (i == (int)strlen(input) && isCharInArray == NULL)
        {
            possibleChars[possibleCharsInputIndex] = toupper(address[i]);
            possibleCharsInputIndex++;

            // save the first thing that gets passed into possibleChars,
            // for when that thing is the only one passed there i know
            // what is the whole address
            if (strlen(possibleChars) == 1)
                strcat(possibleString, address);
        }
    }

    if (strlen(possibleChars) == 0)
    {
        printf("Not found\n");
    }
    else if (strlen(possibleChars) == 1)
    {
        printf("Found: %s\n", possibleString);
    }
    else
    {
        printf("Enable: %s\n", possibleChars);
    }

    return 0;
}