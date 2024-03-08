#include "utilities.h"

void parentProcess(int fd[], char *message, int choice) {
    char buffer[1024];
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    printf(COLOR_YELLOW "Parent Process: Sending '" COLOR_WHITE "%s" COLOR_YELLOW "' to Child" COLOR_RESET "\n", message);
    // First, send the operation code to the child
    if (write(fd[PARENT_WRITE], &choice, sizeof(choice)) != sizeof(choice)) {
        fprintf(stderr, COLOR_WHITE "Parent write (operation code) failed" COLOR_RESET "\n");
        exit(EXIT_FAILURE);
    }

    // Then, send the message
    if (write(fd[PARENT_WRITE], message, strlen(message) + 1) != strlen(message) + 1) {
        fprintf(stderr, COLOR_WHITE "Parent write (message) failed" COLOR_RESET "\n");
        exit(EXIT_FAILURE);
    }

    // Wait for the modified message from the child
    int length = read(fd[PARENT_READ], buffer, sizeof(buffer));
    if (length < 0) {
        fprintf(stderr, COLOR_WHITE "Parent read failed" COLOR_RESET "\n");
        exit(EXIT_FAILURE);
    }
    buffer[length] = '\0';

    printf(COLOR_YELLOW "Parent Process: Received '" COLOR_WHITE "%s" COLOR_YELLOW "' from Child" COLOR_RESET "\n", buffer);

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL);
}
