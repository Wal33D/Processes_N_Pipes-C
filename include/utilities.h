#ifndef UTILITIES_H
#define UTILITIES_H

// Standard library includes
#include <assert.h>
#include <ctype.h>      // For isalpha, tolower, toupper
#include <stdbool.h>    // For bool type
#include <stdio.h>      // For fprintf, printf, perror
#include <stdlib.h>     // For malloc, free, exit
#include <string.h>     // For strlen, strcpy
#include <unistd.h>
#include <sys/wait.h>

// Definitions for pipe indices and the number of pipe pairs
#define CHILD_READ   2
#define CHILD_WRITE  1
#define PARENT_READ  0
#define PARENT_WRITE 3
#define PIPE_PAIRS   2

// ANSI Color Code Definitions
#define COLOR_CYAN   "\x1b[36m"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_RESET  "\x1b[0m"
#define COLOR_WHITE  "\x1b[37m"
#define COLOR_YELLOW "\x1b[33m"

// Function declarations
char *toggleString(const char *input);
int inputValidation(int argc, char *argv[]);
void childProcess(int fd[], StringOperation op);
void parentProcess(int fd[], char *message);
void createPalindrome(char *word); 

typedef char *(*StringOperation)(const char *input);

#endif // UTILITIES_H
