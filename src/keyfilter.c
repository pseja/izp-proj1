/*
 * @file keyfilter.c
 * @author Lukáš Pšeja (xpsejal00)
 * @date 2023-10-18
 * @brief Implements automatic keyboard character bidding based on input
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 103 // maximum length of line + '\0', '\n', '\r', has to be longer by 1 or 2 to later check if the line is longer
#define MAX_UNIQUE_CHARS 69 // ascii characters from 32 to 126 without small letters

// Error codes
#define ERR_UNEXPECTED_CHAR -1
#define ERR_OK 0
#define ERR_FAIL 1
#define ERR_TOO_MANY_ARGS 2
#define ERR_TOO_LONG_LINE 3

// Function prototypes
int handleInput(int argc, char **input);
int calculateInputIndex(char c);
void handleOutput(int found, char *possibleString, char *possibleChars);

int handleInput(int argc, char **input)
{
    // No arguments passed except the program name and file
    // could check with unistd.h if file was passed through terminal
    // but the library works only for unix systems
    if (argc == 1)
    {
        *input = "";
    }
    else if (argc > 2)
    {
        fprintf(stderr, "Too many arguments.\n");
        return ERR_TOO_MANY_ARGS;
    }
    return ERR_OK;
}

// Moving the ascii table to index 0 from whitespace(32) to `(96)
// skipping small letters(97-122) because they will never occur, because
// of toupper(c) getting passed into the function and then from {(123)
// to ~(126) if character is not in the specified range, the function
// prints error message
int calculateInputIndex(char c)
{
    if (c >= ' ' && c <= '`')
    {
        return c - ' ';
    }
    else if (c >= '{' && c <= '~')
    {
        return c - ':';
    }
    fprintf(stderr, "Unexpected character\n");
    return ERR_UNEXPECTED_CHAR;
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

    // Check if the input is valid
    if (handleInput(argc, &input) != ERR_OK)
    {
        return ERR_FAIL;
    }

    char address[MAX_LINE_LENGTH];
    char possibleChars[MAX_UNIQUE_CHARS] = {'\0'};
    char possibleString[MAX_LINE_LENGTH] = {'\0'};
    int found = 0;
    int lengthOfInput = (int)strlen(input);

    // Loads lines to address variable until end of file is reached
    while (fgets(address, MAX_LINE_LENGTH, stdin) != NULL)
    {
        if (strlen(address) > MAX_LINE_LENGTH - 2)
        {
            fprintf(stderr, "Found line longer than the maximum line length\n");
            return ERR_TOO_LONG_LINE;
        }

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
        if (strlen(address) == strlen(input) + 1 && i == lengthOfInput)
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
            if (inputIndex == ERR_UNEXPECTED_CHAR)
            {
                return ERR_FAIL;
            }
            possibleChars[inputIndex] = toupper(address[i]);
        }
    }
    handleOutput(found, possibleString, possibleChars);

    return ERR_OK;
}