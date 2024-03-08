#include "utilities.h"

void parentProcess(int fd[], char *message) {
    int length;
    char parentMessage[strlen(message) + 1];

    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    printf(COLOR_YELLOW "Parent Process: Sending '" COLOR_WHITE "%s" COLOR_YELLOW "' to Child" COLOR_RESET "\n", message);
    if (write(fd[PARENT_WRITE], message, strlen(message)) != strlen(message)) {
        fprintf(stderr, COLOR_WHITE "Parent write failed" COLOR_RESET "\n");
        exit(EXIT_FAILURE);
    }

    length = read(fd[PARENT_READ], &parentMessage, sizeof(parentMessage) - 1);
    if (length < 0) {
        fprintf(stderr, COLOR_WHITE "Parent read failed" COLOR_RESET "\n");
        exit(EXIT_FAILURE);
    }
    parentMessage[length] = '\0';

    printf(COLOR_YELLOW "Parent Process: Received '" COLOR_WHITE "%s" COLOR_YELLOW "' from Child" COLOR_RESET "\n", parentMessage);

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL);
}
