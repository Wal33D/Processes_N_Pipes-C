#include "utilities.h"

void childProcess(int fd[], StringOperation op)
{
    char buffer[1024];
    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);

    int length = read(fd[CHILD_READ], buffer, sizeof(buffer) - 1);
    if (length < 0)
    {
        perror("Child read failed");
        exit(EXIT_FAILURE);
    }
    buffer[length] = '\0';

    char *modifiedMessage = op(buffer); // Apply the operation
    write(fd[CHILD_WRITE], modifiedMessage, strlen(modifiedMessage) + 1);
    free(modifiedMessage); // Ensure to free the memory allocated by the operation

    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}