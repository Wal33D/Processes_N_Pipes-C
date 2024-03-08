#include <unistd.h>
#include <sys/wait.h>
#include "utilities.h"

void parentProcess(int fd[], char *message) {
    int length;
    char parentMessage[strlen(message) + 1]; // Adjust for null terminator

    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    printf("\x1b[33mParent Process: Sending '\x1b[37m%s\x1b[33m' to Child\x1b[0m\n", message);
    if (write(fd[PARENT_WRITE], message, strlen(message)) != strlen(message)) {
        fprintf(stderr, "\x1b[37mParent write failed\x1b[0m\n");
        exit(EXIT_FAILURE);
    }

    length = read(fd[PARENT_READ], &parentMessage, sizeof(parentMessage) - 1);
    if (length < 0) {
        fprintf(stderr, "\x1b[37mParent read failed\x1b[0m\n");
        exit(EXIT_FAILURE);
    }
    parentMessage[length] = '\0'; // Ensure null-termination

    // Display the modified message in yellow with the message part in white
    printf("\x1b[33mParent Process: Received '\x1b[37m%s\x1b[33m' from Child\x1b[0m\n", parentMessage);

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL);
}
