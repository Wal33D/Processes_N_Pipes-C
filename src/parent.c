#include "utilities.h"

void parentProcess(int fd[], char *message, int choice) {
    char buffer[1024];
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    // First, send the operation code to the child
    write(fd[PARENT_WRITE], &choice, sizeof(choice));

    // Then, send the message
    write(fd[PARENT_WRITE], message, strlen(message) + 1);

    // Wait for the modified message from the child
    int length = read(fd[PARENT_READ], buffer, sizeof(buffer));
    if (length < 0) {
        perror("Parent read failed");
        exit(EXIT_FAILURE);
    }
    buffer[length] = '\0';

    printf("Parent Process: Received '%s'\n", buffer);

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL);
}
