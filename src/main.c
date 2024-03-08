#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include "utilities.h"

// Define pipe indices for readability
#define PARENT_READ  0
#define CHILD_WRITE  1
#define CHILD_READ   2
#define PARENT_WRITE 3

// Number of pipe pairs
#define PIPE_PAIRS 2

/**
 * @brief Entry point. This application demonstrates IPC using pipes by toggling
 *        the case of a string passed as a command line argument.
 * 
 * The parent process sends a string to the child process via a pipe. The child
 * process toggles the case of the string (upper to lower, lower to upper) and
 * sends it back to the parent through another pipe. The parent then prints the
 * modified string to the console.
 * 
 * Example usage:
 * ./thisProgram "Hello World" -> outputs "hELLO wORLD"
 * 
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return int Program exit status
 */
int main(int argc, char *argv[]) {
    assert(argc > 1); // Ensure at least one argument is provided

    int fd[2 * PIPE_PAIRS]; // File descriptors for the pipes
    int length; // Variable to store message length
    pid_t pid; // Process ID

    // Buffers for the parent and child messages
    char parentMessage[strlen(argv[1])]; 
    char childMessage[strlen(argv[1])]; 

    // Verify proper input
    if (inputValidation(argc, argv) == 0) {
        strcpy(parentMessage, argv[1]);
    }

    // Initialize pipes
    for (int i = 0; i < PIPE_PAIRS; ++i) {
        if (pipe(fd + (i * 2)) < 0) {
            perror("Pipe initialization failed");
            exit(EXIT_FAILURE);
        }
    }

    // Create child process
    if ((pid = fork()) < 0) {
        perror("Failed to fork process");
        exit(EXIT_FAILURE);
    }

    // Child process code
    if (pid == 0) {
        // Close unused file descriptors
        close(fd[PARENT_READ]);
        close(fd[PARENT_WRITE]);

        // Read the message from the parent
        length = read(fd[CHILD_READ], &childMessage, sizeof(childMessage));
        if (length < 0) {
            perror("Child read failed");
            exit(EXIT_FAILURE);
        }

        // Log and toggle message case
        printf("Child Process: Received '%s'\n", childMessage);
        if (write(fd[CHILD_WRITE], toggleString(childMessage), strlen(childMessage)) < 0) {
            perror("Child write failed");
            exit(EXIT_FAILURE);
        }

        // Close file descriptors and exit
        close(fd[CHILD_READ]);
        close(fd[CHILD_WRITE]);
        return EXIT_SUCCESS;
    }

    // Parent process code
    // Close unused file descriptors
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    // Send the message to the child
    printf("Parent Process: Sending '%s' to Child\n", argv[1]);
    if (write(fd[PARENT_WRITE], argv[1], strlen(argv[1])) != strlen(argv[1])) {
        perror("Parent write failed");
        exit(EXIT_FAILURE);
    }

    // Read the modified message from the child
    length = read(fd[PARENT_READ], &parentMessage, sizeof(parentMessage));
    if (length < 0) {
        perror("Parent read failed");
        exit(EXIT_FAILURE);
    }

    // Display the modified message
    printf("Parent Process: Received '%s' from Child\n", parentMessage);

    // Clean up
    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL); // Wait for child process to terminate

    return EXIT_SUCCESS;
}
