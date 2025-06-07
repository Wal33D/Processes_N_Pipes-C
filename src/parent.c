#include "utilities.h"

void parentProcess(int fd[], char *message, Operation choice)
{
    // Close unused ends of the pipes
    MY_CLOSE(fd[CHILD_READ]);
    MY_CLOSE(fd[CHILD_WRITE]);

    // A playful message for sending the operation to the child
    switch (choice)
    {
    case OP_TOGGLE:
        printf(COLOR_GREEN "Parent whispers: " COLOR_RESET "Hey Kiddo, can you " COLOR_YELLOW "toggle" COLOR_RESET " this for me? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case OP_UPPERCASE:
        printf(COLOR_GREEN "Parent muses: " COLOR_RESET "Hey Kiddo, could you please " COLOR_YELLOW "shout" COLOR_RESET " this out loud? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case OP_PALINDROME:
        printf(COLOR_GREEN "Parent ponders: " COLOR_RESET "Oh, what if we made this " COLOR_YELLOW "mirror" COLOR_RESET " itself? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case OP_RANDOM_MATH:
        // Correctly interpret the message as a pointer to an integer
        int *pNumber = (int *)message;
        printf(COLOR_GREEN "Parent quizzes: " COLOR_RESET "I wonder how we can play with the number " COLOR_YELLOW "%d" COLOR_RESET " today?\n", *pNumber);
        // Then send the number to the child
        if (robustWrite(fd[PARENT_WRITE], pNumber, sizeof(int)) < 0)
            exit(EXIT_FAILURE);
        break;
    default:
        printf(COLOR_GREEN "Parent is confused: " COLOR_RESET "Hmm, not sure what you want, but let's try '" COLOR_WHITE "%s" COLOR_RESET "' anyway.\n", message);
        break;
    }
    MY_SLEEP(delaySeconds);

    // Send the operation code to the child
    fprintf(stderr, COLOR_WHITE "Parent: " COLOR_RESET "Sending Message to Child Process...\n");

    if (robustWrite(fd[PARENT_WRITE], &choice, sizeof(choice)) != sizeof(choice))
    {
        fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oh dear, I couldn't get your sibling to listen...\n");
        exit(EXIT_FAILURE);
    }

    if (choice != OP_RANDOM_MATH)
    {
        // Send the message for string operations
        MY_SLEEP(delaySeconds);
        if (robustWrite(fd[PARENT_WRITE], message, strlen(message) + 1) != (ssize_t)(strlen(message) + 1))
        {
            fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oopsie daisy, my message got lost in the mail...\n");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for and display the modified message or result from the child
    if (choice == OP_RANDOM_MATH)
    {
        int result;
        MY_SLEEP(delaySeconds);
        if (robustRead(fd[PARENT_READ], &result, sizeof(result)) < 0)
        {
            fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Gosh, I never heard back. Are they ignoring me?\n");
            exit(EXIT_FAILURE);
        }
        printf(COLOR_GREEN "Parent beams proudly: " COLOR_RESET "Look! The number magic turned it into " COLOR_YELLOW "%d" COLOR_RESET "!\n", result);
    }
    else
    {
        char buffer[1024];
        MY_SLEEP(delaySeconds);
        int length = robustRead(fd[PARENT_READ], buffer, sizeof(buffer));
        if (length < 0)
        {
            fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Gosh, I never heard back. Are they ignoring me?\n");
            exit(EXIT_FAILURE);
        }
        buffer[length] = '\0';
        printf(COLOR_GREEN "Parent beams proudly: " COLOR_RESET "Oh, look at what my clever child did! --> '" COLOR_YELLOW "%s" COLOR_RESET "'\n", buffer);
    }

    MY_CLOSE(fd[PARENT_READ]);
    MY_CLOSE(fd[PARENT_WRITE]);
    // The main function will handle waiting for the child
    // wait(NULL); // Wait for the child process to terminate
}
