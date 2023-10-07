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

    for (int i = 0; i < ALPHABET_LENGTH; i++)
        possibleChars[i] = '\0';

    char possibleString[MAX_LINE_LENGTH];
    int found = 0;

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
        if (i == (int)strlen(input))
        {
            // save the first thing that gets passed into possibleChars,
            // for when that thing is the only one passed there i know
            // what is the whole address
            if (found == 0)
                strcat(possibleString, address);

            found++;
            int inputIndex = toupper(address[i]) - 'A';
            possibleChars[inputIndex] = toupper(address[i]);
        }
    }

    if (found == 0)
    {
        printf("Not found\n");
    }
    else if (found == 1)
    {
        printf("Found: %s\n", possibleString);
    }
    else
    {
        printf("Enable: ");
        for (int i = 0; i < ALPHABET_LENGTH; i++)
        {
            if (possibleChars[i] != '\0')
                printf("%c", possibleChars[i]);
        }
        printf("\n");
    }

    return 0;
}