#include "utilities.h"

void childProcess(int fd[], int choice) {
    // Close unused ends of the pipes
    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    
    // First, read the operation code
    int opCode;
    read(fd[CHILD_READ], &opCode, sizeof(opCode));

    char buffer[1024];
    int length = read(fd[CHILD_READ], buffer, sizeof(buffer) - 1);
    if (length < 0) {
        perror("Little one stumbled: ");
        exit(EXIT_FAILURE);
    }
    buffer[length] = '\0'; // Null-terminate the string

    char *modifiedMessage;
    // Enthusiastically accepting the task
    switch(opCode) {
        case 1: // Toggle case
            printf(COLOR_CYAN "Child giggles: " COLOR_RESET "Oh, I love playing with case! Watch this!\n");
            modifiedMessage = toggleString(buffer);
            break;
        case 2: // Uppercase
            printf(COLOR_CYAN "Child shouts: " COLOR_RESET "I'll shout this back, louder and prouder!\n");
            modifiedMessage = uppercaseOperation(buffer);
            break;
        case 3: // Create Palindrome
            printf(COLOR_CYAN "Child muses: " COLOR_RESET "Mirroring is fun, let's make a palindrome!\n");
            modifiedMessage = createPalindrome(buffer);
            break;
        default:
            printf(COLOR_CYAN "Child is puzzled but obliges: " COLOR_RESET "I'm not quite sure, but here you go!\n");
            modifiedMessage = strdup(buffer); // Default action: echo the message
            break;
    }

    // Cheerfully sending the modified message back
    write(fd[CHILD_WRITE], modifiedMessage, strlen(modifiedMessage) + 1);
    printf(COLOR_CYAN "Child beams: " COLOR_RESET "Done! Sending it back now!\n");
    
    free(modifiedMessage); // Free the dynamically allocated memory

    // Close the pipes and exit
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}
