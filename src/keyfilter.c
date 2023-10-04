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

    if (argc < 2)
    {
        printf("No arguments passed!\n");
        return 1;
    }

    printf("input: %s\n", input);

    // Loads lines to address variable until end of file is reached 
    while (fgets(address, MAX_LINE_LENGTH, stdin) != NULL)
    {
        for (int i = 0; i < (int)strlen(address); i++)
        {
            printf("%c", address[i]);
        }
    }

    // print possible character
    for (int k = 0; k < 10; k++)    
    {
        printf("%c\n", possibleChars[k]);
    }

    return 0;
}