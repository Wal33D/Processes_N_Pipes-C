#include "utilities.h"

/*
 * child.c - Implementation of the child side of the IPC demos.
 *
 * The child waits for requests from the parent through a pipe,
 * processes the input according to the selected menu option, and
 * sends the result back.  Additional commentary explains each step of
 * the exchange so that the data flow is clear.
 */

void childProcess(int fd[], Operation choice)
{
    /* Close the ends of the pipes the child will not use. */
    MY_CLOSE(fd[PARENT_READ]);
    MY_CLOSE(fd[PARENT_WRITE]);
    if (choice == OP_RANDOM_MATH)
    {
        /* The parent has requested a random math operation. */
        int number;
        MY_SLEEP(delaySeconds);
        if (robustRead(fd[CHILD_READ], &number, sizeof(number)) < 0)
            exit(EXIT_FAILURE);

        srand(time(NULL)); // Seed the random number generator
        int originalNumber = number; // Keep the original number for printing
        number = randomMathOperation(number);
        printf(COLOR_CYAN "Child processed number: " COLOR_RESET "%d -> %d\n", originalNumber, number);

        /* Send the result back to the parent */
        MY_SLEEP(delaySeconds);
        if (robustWrite(fd[CHILD_WRITE], &number, sizeof(number)) < 0)
            exit(EXIT_FAILURE);
        printf(COLOR_CYAN "Child smiles: " COLOR_RESET "All done with the numbers! Sending back a surprise!\n");
    }
    else
    {
        /* First, read the operation code sent by the parent so we know
         * which transformation to apply. */
        Operation opCode;
        MY_SLEEP(delaySeconds);
        if (robustRead(fd[CHILD_READ], &opCode, sizeof(opCode)) < 0)
            exit(EXIT_FAILURE);

        char buffer[1024];
        int length = robustRead(fd[CHILD_READ], buffer, sizeof(buffer) - 1);
        if (length < 0)
            exit(EXIT_FAILURE);
        buffer[length] = '\0'; // Null-terminate the string

        char *modifiedMessage;
        /* Act on the requested transformation. */
        switch (opCode)
        {
        case OP_TOGGLE:
            printf(COLOR_CYAN "Child giggles: " COLOR_RESET "Oh, I love playing with case! Watch this!\n");
            modifiedMessage = toggleString(buffer);
            break;
        case OP_UPPERCASE:
            printf(COLOR_CYAN "Child shouts: " COLOR_RESET "I'll shout this back, louder and prouder!\n");
            modifiedMessage = uppercaseOperation(buffer);
            break;
        case OP_PALINDROME:
            printf(COLOR_CYAN "Child muses: " COLOR_RESET "Mirroring is fun, let's make a palindrome!\n");
            modifiedMessage = createPalindrome(buffer);
            break;
        default:
            printf(COLOR_CYAN "Child is puzzled but obliges: " COLOR_RESET "I'm not quite sure, but here you go!\n");
            modifiedMessage = strdup(buffer); // Default action: echo the message
            break;
        }

        /* Send the modified string back to the parent. */
        printf(COLOR_CYAN "Child beams: " COLOR_RESET "Done! Sending it back now!\n");
        MY_SLEEP(delaySeconds);
        if (robustWrite(fd[CHILD_WRITE], modifiedMessage, strlen(modifiedMessage) + 1) < 0)
            exit(EXIT_FAILURE);

        free(modifiedMessage); // Free the dynamically allocated memory
    }

    /* Clean up and exit. */
    MY_CLOSE(fd[CHILD_READ]);
    MY_CLOSE(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}
