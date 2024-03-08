#include "utilities.h"

void parentProcess(int fd[], char *message, int choice)
{
    // Close unused ends of the pipes
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    // A playful message for sending the operation to the child
    switch (choice)
    {
    case 1:
        printf(COLOR_GREEN "Parent whispers: " COLOR_RESET "Hey sweetie, can you " COLOR_YELLOW "toggle" COLOR_RESET " this for me? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case 2:
        printf(COLOR_GREEN "Parent muses: " COLOR_RESET "Darling, could you please " COLOR_YELLOW "shout" COLOR_RESET " this out loud? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case 3:
        printf(COLOR_GREEN "Parent ponders: " COLOR_RESET "Oh, what if we made this " COLOR_YELLOW "mirror" COLOR_RESET " itself? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case 4:
        // Assuming you somehow convert 'message' to an integer 'number'
        int number = atoi(message); // Convert the input string to an integer
        printf(COLOR_GREEN "Parent quizzes: " COLOR_RESET "I wonder how we can play with the number " COLOR_YELLOW "%d" COLOR_RESET " today?\n", number);

        break;
    default:
        printf(COLOR_GREEN "Parent is confused: " COLOR_RESET "Hmm, not sure what you want, but let's try '" COLOR_WHITE "%s" COLOR_RESET "' anyway.\n", message);
        break;
    }

    // Send the operation code to the child
    if (write(fd[PARENT_WRITE], &choice, sizeof(choice)) != sizeof(choice))
    {
        fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oh dear, I couldn't get your sibling to listen...\n");
        exit(EXIT_FAILURE);
    }

    if (choice == 4)
    {
        // For math operations, convert the message to an integer and send it
        int number = atoi(message); // Assuming the message is a number for case 4
        if (write(fd[PARENT_WRITE], &number, sizeof(number)) != sizeof(number))
        {
            fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Seems like my math question got lost...\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // Send the message for string operations
        if (write(fd[PARENT_WRITE], message, strlen(message) + 1) != strlen(message) + 1)
        {
            fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oopsie daisy, my message got lost in the mail...\n");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for and display the modified message or result from the child
    if (choice == 4)
    {
        int result;
        if (read(fd[PARENT_READ], &result, sizeof(result)) < 0)
        {
            fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Gosh, I never heard back. Are they ignoring me?\n");
            exit(EXIT_FAILURE);
        }
        printf(COLOR_GREEN "Parent beams proudly: " COLOR_RESET "Look! The number magic turned it into " COLOR_YELLOW "%d" COLOR_RESET "!\n", result);
    }
    else
    {
        char buffer[1024];
        int length = read(fd[PARENT_READ], buffer, sizeof(buffer));
        if (length < 0)
        {
            fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Gosh, I never heard back. Are they ignoring me?\n");
            exit(EXIT_FAILURE);
        }
        buffer[length] = '\0';
        printf(COLOR_GREEN "Parent beams proudly: " COLOR_RESET "Oh, look at what my clever child did! --> '" COLOR_YELLOW "%s" COLOR_RESET "'\n", buffer);
    }

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL); // Wait for the child process to terminate
}
