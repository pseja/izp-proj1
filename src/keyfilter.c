#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 103 // maximum length of line + '\0' + '\n' + '\r'
#define MAX_UNIQUE_CHARS 69 // ascii characters from 32 to 126 without small letters

int handleInput(int argc, char **input);
int calculateInputIndex(char c);
void handleOutput(int found, char *possibleString, char *possibleChars);

int handleInput(int argc, char **input)
{
    // Checks if a file was passed as an argument to stdin
    if (isatty(STDIN_FILENO))
    {
        printf("No file passed to stdin.\n");
        return -1;
    }

    // No arguments passed except the program name
    if (argc == 1)
    {
        *input = "";
    }
    else if (argc > 2)
    {
        printf("Too many arguments.\n");
        return -2;
    }

    return 0; // OK
}

// Moving the ascii table to index 0 from whitespace(32) to `(96)
// skipping small letters(97-122) because they will never occur, because
// of toupper(c) getting passed into the function and then from {(123)
// to ~(126)
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
    fprintf(stderr, "Unexpected character\n");
    return -1;
}

void handleOutput(int found, char *possibleString, char *possibleChars)
{
    if (found == 0)
    {
        printf("Not found\n");
    }
    else if (found == 1)
    {
        printf("Found: ");
        for (int i = 0; i < MAX_LINE_LENGTH; i++)
        {
            printf("%c", toupper(possibleString[i]));
        }
    }
    else
    {
        printf("Enable: ");
        for (int i = 0; i < MAX_UNIQUE_CHARS; i++)
        {
            if (possibleChars[i] != '\0')
            {
                printf("%c", possibleChars[i]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    char *input = argv[1];

    // Check if the input is correct
    if (handleInput(argc, &input) != 0)
    {
        return 1;
    }

    char address[MAX_LINE_LENGTH];
    char possibleChars[MAX_UNIQUE_CHARS];
    char possibleString[MAX_LINE_LENGTH];
    int found = 0;
    int lengthOfInput = (int)strlen(input);

    // Initializing array with '\0' to later input chars
    for (int i = 0; i < MAX_UNIQUE_CHARS; i++)
    {
        possibleChars[i] = '\0';
    }

    // Loads lines to address variable until end of file is reached 
    while (fgets(address, MAX_LINE_LENGTH, stdin) != NULL)
    {
        int i;

        for (i = 0; i < lengthOfInput; i++)
        {
            // If non matching character was found, break
            if (toupper(input[i]) != toupper(address[i]))
            {
                break;
            }
        }

        // If the input is the same length + 1 (because of '\0' in address) 
        // as the address and for loop passed all letters
        // we have found the address we were looking for
        if (strlen(address) == strlen(input)+1 && i == lengthOfInput)
        {
            strcat(possibleString, address);
            found = 1;
            break;
        }
        // Check if for loop matched the correct string with input
        else if (i == lengthOfInput)
        {
            // Save the first address of the char that gets passed into possibleChars,
            // for when that char is the only one passed there we know
            // what is the whole address
            if (found == 0)
            {
                strcat(possibleString, address);
            }

            found++;
            // Calculate where to put the current character
            int inputIndex = calculateInputIndex(toupper(address[i]));
            if (inputIndex == -1)
            {
                return 2;
            }
            possibleChars[inputIndex] = toupper(address[i]);
        }
    }
    handleOutput(found, possibleString, possibleChars);

    return 0;
}