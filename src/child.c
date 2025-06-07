#include "utilities.h"

void childProcess(int fd[], int choice)
{
    // Close unused ends of the pipes
    MY_CLOSE(fd[PARENT_READ]);
    MY_CLOSE(fd[PARENT_WRITE]);
    if (choice == 4)
    {
        // Handling a random math operation
        int number;
        MY_SLEEP(delaySeconds);
        if (robustRead(fd[CHILD_READ], &number, sizeof(number)) < 0)
            exit(EXIT_FAILURE);

        srand(time(NULL)); // Seed the random number generator
        int originalNumber = number; // Keep the original number for printing
        number = randomMathOperation(number);
        printf(COLOR_CYAN "Child processed number: " COLOR_RESET "%d -> %d\n", originalNumber, number);

        // Send the result back to the parent
        MY_SLEEP(delaySeconds);
        if (robustWrite(fd[CHILD_WRITE], &number, sizeof(number)) < 0)
            exit(EXIT_FAILURE);
        printf(COLOR_CYAN "Child smiles: " COLOR_RESET "All done with the numbers! Sending back a surprise!\n");
    }
    else
    {
        // First, read the operation code
        int opCode;
        MY_SLEEP(delaySeconds);
        if (robustRead(fd[CHILD_READ], &opCode, sizeof(opCode)) < 0)
            exit(EXIT_FAILURE);

        char buffer[1024];
        int length = robustRead(fd[CHILD_READ], buffer, sizeof(buffer) - 1);
        if (length < 0)
            exit(EXIT_FAILURE);
        buffer[length] = '\0'; // Null-terminate the string

        char *modifiedMessage;
        // Enthusiastically accepting the task
        switch (opCode)
        {
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
        printf(COLOR_CYAN "Child beams: " COLOR_RESET "Done! Sending it back now!\n");
        MY_SLEEP(delaySeconds);
        if (robustWrite(fd[CHILD_WRITE], modifiedMessage, strlen(modifiedMessage) + 1) < 0)
            exit(EXIT_FAILURE);

        free(modifiedMessage); // Free the dynamically allocated memory
    }

    // Close the pipes and exit
    MY_CLOSE(fd[CHILD_READ]);
    MY_CLOSE(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}
