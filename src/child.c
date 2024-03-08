#include "utilities.h"
#include <stdlib.h> // For random number operations
#include <time.h>   // For seeding the random number generator

void childProcess(int fd[], int choice) {
    // Close unused ends of the pipes
    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);

    if (choice == 4) {
        // Handling a random math operation
        int number;
        read(fd[CHILD_READ], &number, sizeof(number));
        srand(time(NULL)); // Seed the random number generator
        int operation = rand() % 3; // Choose a random operation: 0=add, 1=subtract, 2=multiply
        int originalNumber = number; // Keep the original number for printing

        switch (operation) {
            case 0:
                number += rand() % 10; // Add a random value between 0-9
                printf(COLOR_CYAN "Child calculates: " COLOR_RESET "Adding a little bit to %d, we get %d!\n", originalNumber, number);
                break;
            case 1:
                number -= rand() % 10; // Subtract a random value between 0-9
                printf(COLOR_CYAN "Child ponders: " COLOR_RESET "If we take a bit away from %d, it becomes %d!\n", originalNumber, number);
                break;
            case 2:
                number *= (rand() % 3) + 1; // Multiply by a value between 1-3
                printf(COLOR_CYAN "Child dreams: " COLOR_RESET "Multiplying %d... Look! It's now %d!\n", originalNumber, number);
                break;
        }

        // Send the result back to the parent
        write(fd[CHILD_WRITE], &number, sizeof(number));
        printf(COLOR_CYAN "Child smiles: " COLOR_RESET "All done with the numbers! Sending back a surprise!\n");
    } else {
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
    }

    // Close the pipes and exit
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}
