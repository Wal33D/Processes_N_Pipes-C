#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include "utilities.h"

/**
 * @brief Entry point. This application demonstrates IPC using pipes by toggling
 *        the case of a string passed as a command line argument.
 *
 * The parent process sends a string to the child process via a pipe. The child
 * process toggles the case of the string (upper to lower, lower to upper) and
 * sends it back to the parent through another pipe. The parent then prints the
 * modified string to the console in a stylish manner.
 *
 * Example usage:
 * ./thisProgram "Hello World" -> outputs "hELLO wORLD"
 *
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return int Program exit status
 */

#define PARENT_READ 0
#define CHILD_WRITE 1
#define CHILD_READ 2
#define PARENT_WRITE 3
#define PIPE_PAIRS 2

// ANSI escape codes for colors and styles
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void parentProcess(int fd[], char *message)
{
    int length;
    char parentMessage[strlen(message) + 1]; // +1 for null terminator

    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    printf(GREEN "Parent Process: Sending '" MAGENTA "%s" GREEN "' to Child\n" RESET, message);
    if (write(fd[PARENT_WRITE], message, strlen(message)) != strlen(message))
    {
        perror("Parent write failed");
        exit(EXIT_FAILURE);
    }

    length = read(fd[PARENT_READ], &parentMessage, sizeof(parentMessage) - 1);
    if (length < 0)
    {
        perror("Parent read failed");
        exit(EXIT_FAILURE);
    }
    parentMessage[length] = '\0'; // Null-terminate the received string

    printf(BLUE "Parent Process: Received '" YELLOW "%s" BLUE "' from Child\n" RESET, parentMessage);

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL);
}

void childProcess(int fd[])
{
    int length;
    char childMessage[1024];

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);

    length = read(fd[CHILD_READ], &childMessage, sizeof(childMessage) - 1);
    if (length < 0)
    {
        perror("Child read failed");
        exit(EXIT_FAILURE);
    }
    childMessage[length] = '\0'; // Null-terminate the received string

    printf(CYAN "Child Process: Received '" YELLOW "%s" CYAN "'\n" RESET, childMessage);
    if (write(fd[CHILD_WRITE], toggleString(childMessage), strlen(childMessage)) < 0)
    {
        perror("Child write failed");
        exit(EXIT_FAILURE);
    }

    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    assert(argc > 1);

    int fd[2 * PIPE_PAIRS];
    pid_t pid;

    char *message = argv[1];
    if (inputValidation(argc, argv) == 0)
    {
        message = argv[1];
    }

    for (int i = 0; i < PIPE_PAIRS; ++i)
    {
        if (pipe(fd + (i * 2)) < 0)
        {
            perror("Pipe initialization failed");
            exit(EXIT_FAILURE);
        }
    }

    if ((pid = fork()) < 0)
    {
        perror("Failed to fork process");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        childProcess(fd);
    }
    else
    {
        parentProcess(fd, message);
    }

    return EXIT_SUCCESS;
}
