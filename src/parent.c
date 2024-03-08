#include "utilities.h"

void parentProcess(int fd[], char *message) {
    char buffer[1024];
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    write(fd[PARENT_WRITE], message, strlen(message) + 1); // Send the message

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
