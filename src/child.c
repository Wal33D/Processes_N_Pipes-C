#include "utilities.h"

/*
 * childProcess runs in the forked child.  It reads data from the parent,
 * performs the requested transformation and writes the result back.
 */
void childProcess(int fd[], Operation choice)
{
    /* only use the child-specific ends of the pipes */
    MY_CLOSE(fd[PARENT_READ]);
    MY_CLOSE(fd[PARENT_WRITE]);
    if (choice == OP_RANDOM_MATH)
    {
        /* branch: the parent sent us a number to modify */
        int number;
        MY_SLEEP(delaySeconds);
        /* read the integer from the parent */
        if (robustRead(fd[CHILD_READ], &number, sizeof(number)) < 0)
            exit(EXIT_FAILURE);

        /* use current time to seed the random number generator */
        srand(time(NULL));
        int originalNumber = number; // Keep the original number for printing
        number = randomMathOperation(number);
        printf(COLOR_CYAN "Child processed number: " COLOR_RESET "%d -> %d\n", originalNumber, number);

        /* send the result back to the parent */
        MY_SLEEP(delaySeconds);
        if (robustWrite(fd[CHILD_WRITE], &number, sizeof(number)) < 0)
            exit(EXIT_FAILURE);
        printf(COLOR_CYAN "Child smiles: " COLOR_RESET "All done with the numbers! Sending back a surprise!\n");
    }
    else
    {
        /* string manipulation path */
        // First, read the operation code
        Operation opCode;
        MY_SLEEP(delaySeconds);
        if (robustRead(fd[CHILD_READ], &opCode, sizeof(opCode)) < 0)
            exit(EXIT_FAILURE);

        char buffer[1024];
        /* then read the text to operate on */
        int length = robustRead(fd[CHILD_READ], buffer, sizeof(buffer) - 1);
        if (length < 0)
            exit(EXIT_FAILURE);
        buffer[length] = '\0'; // Null-terminate the string

        char *modifiedMessage;
        /* perform the requested string operation */
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

        /* pass the processed string back to the parent */
        printf(COLOR_CYAN "Child beams: " COLOR_RESET "Done! Sending it back now!\n");
        MY_SLEEP(delaySeconds);
        if (robustWrite(fd[CHILD_WRITE], modifiedMessage, strlen(modifiedMessage) + 1) < 0)
            exit(EXIT_FAILURE);

        free(modifiedMessage); // Free the dynamically allocated memory
    }

    /* tidy up and terminate */
    MY_CLOSE(fd[CHILD_READ]);
    MY_CLOSE(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}
