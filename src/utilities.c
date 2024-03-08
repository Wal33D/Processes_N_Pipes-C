#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilities.h"

/*
    toggleString accepts an a pointer to char array, allocates size for the string to be toggled,
    copys the argument into a string, loops through the string and for every uppercase character
    we set it to its lower case counterpart and vice versa, returning the toggled string
*/
char *toggleString(char *argv)
{

    int i; /* Declare counter */

    char *str = malloc(sizeof(argv[1])); /* Declare array sizeof input */

    strcpy(str, argv); /* Copy String to char array */

    for (i = 0; str[i] != '\0'; i++)
    { // Loop through length of string

        if (str[i] >= 'A' && str[i] <= 'Z')
        { // if the array at i is uppercase

            str[i] += 32; // Make it lower case
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        { //  if the array at i is lowercase

            str[i] -= 32; // Make it uppercase
        }
    }

    return str;
}

/*
    int inputValidation accept and integer (number of arugments) and a pointer to the cmd line input array
    We check to see if the command line input contains the minimal number of arugments and check to see
    whether or not the user input contains at least one reversible haracter, if all goes well we return 0
*/
int inputValidation(int argc, char *argv[])
{

    int i; // Declare counter variable

    bool c = false; // Declare boolean flag using imported <stdbool.h>

    char str[strlen(argv[1])]; // Declare str

    strcpy(str, argv[1]); // copy argument into str

    if (argc != 2)
    { // check to see if we have enough arguments to continue
      // Prompt user of correct usage
        fprintf(stderr, "\nUsage: %s <string> or <'string 1, string 2', ..., string n'> for multiple strings\n", argv[0]);

        exit(EXIT_FAILURE); // Exit on improper input
    }
    else
    {
        // loop through our string
        for (i = 0; i < strlen(str); i++)
        {
            // if any any char is a reversible character
            if (isalpha((int)str[i]))
            {

                c = true; // set the flag to true
            }
        }

        if (c == false)
        { // If flag is false input does not contain any reversible charachters

            printf("\nSorry, The string you entered did NOT contain any Alphabetical Characters\nRun me again, with at least 1 Alphabetical character\n\n");

            exit(EXIT_FAILURE); // Exit on improper input
        }

        return (0);
    }
}