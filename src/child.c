#include "utilities.h"

void childProcess(int fd[], int choice)
{
    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);

    if (choice == 4)
    {
        int number;
        read(fd[CHILD_READ], &number, sizeof(number));
        srand(time(NULL));

        int operationNumber = rand() % 10;
        int originalNumber = number;

        switch (rand() % 3)
        {
        case 0:
            number += operationNumber;
            printf(COLOR_CYAN "Child calculates: " COLOR_RESET "Adding %d to %d, we get %d!\n", operationNumber, originalNumber, number);
            break;
        case 1:
            number -= operationNumber;
            printf(COLOR_CYAN "Child ponders: " COLOR_RESET "Taking %d away from %d, it becomes %d!\n", operationNumber, originalNumber, number);
            break;
        case 2:
            operationNumber = (rand() % 3) + 1;
            number *= operationNumber;
            printf(COLOR_CYAN "Child dreams: " COLOR_RESET "Multiplying %d by %d... Look! It's now %d!\n", originalNumber, operationNumber, number);
            break;
        }

        write(fd[CHILD_WRITE], &number, sizeof(number));
        printf(COLOR_CYAN "Child smiles: " COLOR_RESET "All done with the numbers! Sending back a surprise!\n");
    }
    else
    {
        int opCode;
        read(fd[CHILD_READ], &opCode, sizeof(opCode));

        char buffer[1024];
        int length = read(fd[CHILD_READ], buffer, sizeof(buffer) - 1);
        if (length < 0)
        {
            perror("Little one stumbled: ");
            exit(EXIT_FAILURE);
        }
        buffer[length] = '\0';

        char *modifiedMessage;
        switch (opCode)
        {
        case 1:
            modifiedMessage = toggleString(buffer);
            printf(COLOR_CYAN "Child giggles: " COLOR_RESET "Oh, I love playing with case! Watch this!\n");
            break;
        case 2:
            modifiedMessage = uppercaseOperation(buffer);
            printf(COLOR_CYAN "Child shouts: " COLOR_RESET "I'll shout this back, louder and prouder!\n");
            break;
        case 3:
            modifiedMessage = createPalindrome(buffer);
            printf(COLOR_CYAN "Child muses: " COLOR_RESET "Mirroring is fun, let's make a palindrome!\n");
            break;
        default:
            modifiedMessage = strdup(buffer);
            printf(COLOR_CYAN "Child is puzzled but obliges: " COLOR_RESET "I'm not quite sure, but here you go!\n");
            break;
        }

        write(fd[CHILD_WRITE], modifiedMessage, strlen(modifiedMessage) + 1);
        printf(COLOR_CYAN "Child beams: " COLOR_RESET "Done! Sending it back now!\n");

        free(modifiedMessage);
    }

    char thankYouMsg[1024];
    int msgLen = read(fd[CHILD_READ], thankYouMsg, sizeof(thankYouMsg) - 1);
    if (msgLen > 0)
    {
        thankYouMsg[msgLen] = '\0';
        printf(COLOR_CYAN "Child hears: " COLOR_RESET "%s\n", thankYouMsg);

        char responseToParent[] = "No problem, see ya later!";
        write(fd[CHILD_WRITE], responseToParent, sizeof(responseToParent));
    }
    else
    {
        fprintf(stderr, "Error reading 'Thank You' message from parent.\n");
    }

    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);
    exit(EXIT_SUCCESS);
}
