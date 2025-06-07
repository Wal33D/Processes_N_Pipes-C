#ifndef UTILITIES_H
#define UTILITIES_H

// Standard library includes
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>   

// Definitions for pipe indices and the number of pipe pairs
#define CHILD_READ 2
#define CHILD_WRITE 1
#define PARENT_READ 0
#define PARENT_WRITE 3
#define PIPE_PAIRS 2

// ANSI Color Code Definitions
#define COLOR_CYAN "\x1b[36m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"
#define COLOR_WHITE "\x1b[37m"
#define COLOR_YELLOW "\x1b[33m"

// Default delay in seconds used for parent/child communication
#define DEFAULT_DELAY 3

// Global variable holding the actual delay duration
extern int delaySeconds;

// Function declarations
char *toggleString(const char *input);

void childProcess(int fd[], int choice);
void parentProcess(int fd[], char *message, int choice);

char *createPalindrome(const char *word);
char *uppercaseOperation(const char *input);

typedef char *(*StringOperation)(const char *input);

#endif
