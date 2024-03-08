#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "utilities.h"

int main(int argc, char *argv[]) {
    assert(argc > 1);

    int fd[2 * PIPE_PAIRS];
    pid_t pid;
    char *message = argv[1];

    if (inputValidation(argc, argv) == 0) {
        message = argv[1];
    }

    for (int i = 0; i < PIPE_PAIRS; ++i) {
        if (pipe(fd + (i * 2)) < 0) {
            perror("Pipe initialization failed");
            exit(EXIT_FAILURE);
        }
    }

    if ((pid = fork()) < 0) {
        perror("Failed to fork process");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        childProcess(fd);
    } else {
        parentProcess(fd, message);
    }

    return EXIT_SUCCESS;
}
