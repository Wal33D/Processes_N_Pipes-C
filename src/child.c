#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "utilities.h"

void childProcess(int fd[]) {
    int length;
    char childMessage[1024];

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);

    length = read(fd[CHILD_READ], &childMessage, sizeof(childMessage) - 1);
    if (length < 0) {
        fprintf(stderr, "\x1b[37mChild read failed\x1b[0m\n");
        exit(EXIT_FAILURE);
    }
    childMessage[length] = '\0'; // Ensure null-termination

    printf("\x1b[36mChild Process: Received '%s'\x1b[0m\n", childMessage);
    if (write(fd[CHILD_WRITE], toggleString(childMessage), strlen(childMessage)) < 0) {
        fprintf(stderr, "\x1b[37mChild write failed\x1b[0m\n");
        exit(EXIT_FAILURE);
    }

    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}
