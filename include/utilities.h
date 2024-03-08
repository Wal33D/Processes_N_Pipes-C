#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>      // For fprintf, printf, perror
#include <stdlib.h>     // For malloc, free, exit
#include <string.h>     // For strlen, strcpy
#include <ctype.h>      // For isalpha, tolower, toupper
#include <stdbool.h>    // For bool type

#define PARENT_READ  0
#define CHILD_WRITE  1
#define CHILD_READ   2
#define PARENT_WRITE 3

// Function declarations updated
char *toggleString(const char *input); // Updated parameter to const char*
int inputValidation(int argc, char *argv[]);
void parentProcess(int fd[], char *message);
void childProcess(int fd[]);

#endif
