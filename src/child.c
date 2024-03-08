#include "utilities.h"
#include "utilities.c"
void childProcess(int fd[]) {
    // Close unused ends of the pipes
    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    
    // First, read the operation code
    int opCode;
    read(fd[CHILD_READ], &opCode, sizeof(opCode));

    char buffer[1024];
    int length = read(fd[CHILD_READ], buffer, sizeof(buffer) - 1);
    if (length < 0) {
        perror("Child read failed");
        exit(EXIT_FAILURE);
    }
    buffer[length] = '\0'; // Null-terminate the string

    char *modifiedMessage;
    // Decide which operation to perform based on the opCode
    switch(opCode) {
        case 1: // Toggle case
            modifiedMessage = toggleString(buffer);
            break;
        case 2: // Uppercase
            modifiedMessage = uppercaseOperation(buffer);
            break;
        case 3: // Create Palindrome
            modifiedMessage = createPalindrome(buffer);
            break;
        default:
            modifiedMessage = strdup(buffer); // Default action: echo the message
            break;
    }

    // Send the modified message back to the parent
    write(fd[CHILD_WRITE], modifiedMessage, strlen(modifiedMessage) + 1);
    free(modifiedMessage); // Free the dynamically allocated memory

    // Close the pipes and exit
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}
