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

/* Cross platform wrappers for common system calls */
#ifdef _WIN32
#include <io.h>
#include <windows.h>
#define MY_READ  _read
#define MY_WRITE _write
#define MY_CLOSE _close
#define MY_PIPE  _pipe
#define MY_FORK() (-1)  /* fork is not available on Windows */
#define MY_SLEEP(x) Sleep((x)*1000)
#else
#define MY_READ  read
#define MY_WRITE write
#define MY_CLOSE close
#define MY_PIPE  pipe
#define MY_FORK  fork
#define MY_SLEEP(x) sleep(x)
#endif

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

/** Global variable holding the delay between parent and child communication. */
extern int delaySeconds;

/**
 * Read exactly count bytes from a file descriptor.
 * Returns the number of bytes read or -1 on failure.
 */
ssize_t robustRead(int fd, void *buf, size_t count);

/**
 * Write exactly count bytes to a file descriptor.
 * Returns the number of bytes written or -1 on failure.
 */
ssize_t robustWrite(int fd, const void *buf, size_t count);

/** Operation codes sent between the parent and child processes. */
typedef enum
{
    OP_TOGGLE = 1,
    OP_UPPERCASE,
    OP_PALINDROME,
    OP_RANDOM_MATH
} Operation;

// Function declarations
/**
 * Toggle the case of every character in the input string.
 * The returned string must be freed by the caller.
 */
char *toggleString(const char *input);

/** Handle the child side of IPC based on the user's menu choice. */
void childProcess(int fd[], Operation choice);
/** Handle the parent side of IPC based on the user's menu choice. */
void parentProcess(int fd[], char *message, Operation choice);

/**
 * Build a palindrome using the provided word.
 * The returned string must be freed by the caller.
 */
char *createPalindrome(const char *word);
/**
 * Convert the entire input string to uppercase.
 * The returned string must be freed by the caller.
 */
char *uppercaseOperation(const char *input);

/**
 * Perform a random math operation on the given number and return the result.
 */
int randomMathOperation(int number);

#endif
