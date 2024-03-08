#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>      // For fprintf, printf, perror
#include <stdlib.h>     // For malloc, free, exit
#include <string.h>     // For strlen, strcpy
#include <ctype.h>      // For isalpha, tolower, toupper
#include <stdbool.h>    // For bool type

// Function declarations updated
char *toggleString(const char *input); // Updated parameter to const char*
int inputValidation(int argc, char *argv[]);

#endif
