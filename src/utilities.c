#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilities.h"

/*
    toggleString accepts a pointer to a char array, allocates size for the string to be toggled,
    copies the argument into a string, loops through the string, and for every uppercase character
    we set it to its lower case counterpart and vice versa, returning the toggled string.
*/
char *toggleString(char *argv)
{
    int i; // Declare counter

    // Allocate memory for the string plus null terminator
    char *str = malloc(strlen(argv) + 1); // Correct memory allocation

    strcpy(str, argv); // Copy String to char array

    for (i = 0; str[i] != '\0'; i++)
    { // Loop through the length of the string
        if (str[i] >= 'A' && str[i] <= 'Z')
        { // if the character at i is uppercase
            str[i] += 32; // Make it lower case
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        { // if the character at i is lowercase
            str[i] -= 32; // Make it uppercase
        }
    }

    return str;
}

/*
    inputValidation accepts an integer (number of arguments) and a pointer to the cmd line input array.
    We check to see if the command line input contains the minimal number of arguments and check to see
    whether or not the user input contains at least one reversible character, if all goes well we return 0.
*/
int inputValidation(int argc, char *argv[])
{
    int i; // Declare counter variable

    bool c = false; // Declare boolean flag using imported <stdbool.h>

    if (argc != 2)
    { // Check to see if we have enough arguments to continue
      // Prompt user of correct usage
        fprintf(stderr, "\nUsage: %s <string> or <'string 1, string 2', ..., string n'> for multiple strings\n", argv[0]);
        exit(EXIT_FAILURE); // Exit on improper input
    }
    else
    {
        // Loop through our string
        for (i = 0; argv[1][i] != '\0'; i++)
        {
            // If any char is a reversible character
            if (isalpha((int)argv[1][i]))
            {
                c = true; // Set the flag to true
                break; // Break once a reversible character is found
            }
        }

        if (!c)
        { // If flag is false, input does not contain any reversible characters
            printf("\nSorry, The string you entered did NOT contain any Alphabetical Characters\nRun me again, with at least 1 Alphabetical character\n\n");
            exit(EXIT_FAILURE); // Exit on improper input
        }
    }

    return 0; // Proper input was provided
}
