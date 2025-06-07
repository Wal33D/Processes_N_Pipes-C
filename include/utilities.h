#ifndef UTILITIES_H
#define UTILITIES_H

/*
 * Utility functions and shared definitions used across the project.
 * This header provides cross platform wrappers, helper routines and
 * convenience macros for colouring terminal output.
 */

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

/*
 * Cross platform wrappers for common system calls.  These macros allow the
 * code base to compile on both POSIX and Windows environments without
 * sprinkling platform specific #ifdefs throughout the source.
 */
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

/*
 * The parent and child communicate using two pipes: one for each direction of
 * data flow.  The constants below index into the fd array so the code can refer
 * to each pipe end by a meaningful name.
 */
#define CHILD_READ 2
#define CHILD_WRITE 1
#define PARENT_READ 0
#define PARENT_WRITE 3
#define PIPE_PAIRS 2

/* ANSI escape sequences used to print colourful text to the terminal. */
#define COLOR_CYAN "\x1b[36m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"
#define COLOR_WHITE "\x1b[37m"
#define COLOR_YELLOW "\x1b[33m"

/* Default delay (in seconds) inserted between pipe communications. */
#define DEFAULT_DELAY 3

/**
 * Number of seconds the parent and child pause before sending or receiving
 * messages.  main.c can override this at runtime.
 */
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

/**
 * Operation codes sent between the parent and child processes.  The parent
 * selects one of these actions from the menu and the child performs the
 * associated transformation.
 */
typedef enum
{
    OP_TOGGLE = 1,   /* invert the case of each character */
    OP_UPPERCASE,    /* convert a string to all uppercase   */
    OP_PALINDROME,   /* mirror the string to form a palindrome */
    OP_RANDOM_MATH   /* perform a random arithmetic operation */
} Operation;

// Function declarations
/**
 * Toggle the case of every character in the input string.
 * The returned string must be freed by the caller.
 */
char *toggleString(const char *input);

/**
 * Spawned in the child after fork().
 * Receives commands from the parent through the pipe and sends the processed
 * response back.
 */
void childProcess(int fd[], Operation choice);
/**
 * Runs in the parent process.  Sends the chosen operation and message to the
 * child and then waits for the response.
 */
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
