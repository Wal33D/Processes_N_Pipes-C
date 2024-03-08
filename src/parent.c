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
        printf(COLOR_GREEN "Parent whispers: " COLOR_RESET "Hey Kiddo, can you " COLOR_YELLOW "toggle" COLOR_RESET " this for me? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case 2:
        printf(COLOR_GREEN "Parent muses: " COLOR_RESET "Hey Kiddo, could you please " COLOR_YELLOW "shout" COLOR_RESET " this out loud? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case 3:
        printf(COLOR_GREEN "Parent ponders: " COLOR_RESET "Oh, what if we made this " COLOR_YELLOW "mirror" COLOR_RESET " itself? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case 4:
        // Correctly interpret the message as a pointer to an integer
        int *pNumber = (int *)message;
        printf(COLOR_GREEN "Parent quizzes: " COLOR_RESET "I wonder how we can play with the number " COLOR_YELLOW "%d" COLOR_RESET " today?\n", *pNumber);
        // Then send the number to the child
        write(fd[PARENT_WRITE], pNumber, sizeof(int));
        break;
    default:
        printf(COLOR_GREEN "Parent is confused: " COLOR_RESET "Hmm, not sure what you want, but let's try '" COLOR_WHITE "%s" COLOR_RESET "' anyway.\n", message);
        break;
    }
    sleep(3);

    // Send the operation code to the child
    fprintf(stderr, COLOR_WHITE "Parent: " COLOR_RESET "Sending Message to Child Process...\n");

    if (write(fd[PARENT_WRITE], &choice, sizeof(choice)) != sizeof(choice))
    {
        fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oh dear, I couldn't get your sibling to listen...\n");
        exit(EXIT_FAILURE);
    }

    if (choice != 4)
    {
        // Send the message for string operations
        sleep(3);
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
        sleep(3);
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
        sleep(3);
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
