#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>      // For fprintf, printf, perror
#include <stdlib.h>     // For malloc, free, exit
#include <string.h>     // For strlen, strcpy
#include <ctype.h>      // For isalpha
#include <stdbool.h>    // For bool type

// Function declarations
char *toggleString(char *argv);
int inputValidation(int argc, char *argv[]);

#endif
