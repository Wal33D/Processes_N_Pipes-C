#include "utilities.h"

void childProcess(int fd[]) {
    int length;
    char childMessage[1024];

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);

    length = read(fd[CHILD_READ], &childMessage, sizeof(childMessage) - 1);
    if (length < 0) {
        fprintf(stderr, COLOR_WHITE "Child read failed" COLOR_RESET "\n");
        exit(EXIT_FAILURE);
    }
    childMessage[length] = '\0';

    printf(COLOR_CYAN "Child Process: Received '" COLOR_WHITE "%s" COLOR_CYAN "'" COLOR_RESET "\n", childMessage);
    if (write(fd[CHILD_WRITE], toggleString(childMessage), strlen(childMessage)) < 0) {
        fprintf(stderr, COLOR_WHITE "Child write failed" COLOR_RESET "\n");
        exit(EXIT_FAILURE);
    }

    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}
