#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define ALPHABET_LENGTH 26

int main(int argc, char *argv[])
{
    // proměnné
    char *input = argv[1];
    char address[MAX_LINE_LENGTH];
    char possibleChars[ALPHABET_LENGTH];
    int possibleCharsInputIndex = 0;

    if (argc < 2)
    {
        printf("No arguments passed!\n");
        return 1;
    }

    // printf("input: %s\n", input);

    // Loads lines to address variable until end of file is reached 
    while (fgets(address, MAX_LINE_LENGTH, stdin) != NULL)
    {
        int i;
        for (i = 0; i < (int)strlen(input); i++)
        {
            if (input[i] != address[i])
                break;
            // printf("%c", address[i]);
        }

        if (i == (int)strlen(input))
        {
            possibleChars[possibleCharsInputIndex] = address[i];
            possibleCharsInputIndex++;
        }
    }

    // print first ten possible characters (going to be changing this later, now only for testing)
    for (int k = 0; k < 10; k++)    
    {
        if (possibleChars[k] == 0)
            continue;
        printf("%c", possibleChars[k]);
    }
    printf("\n");

    return 0;
}