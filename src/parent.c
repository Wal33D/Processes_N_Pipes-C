#include "utilities.h"

/*
 * parentProcess orchestrates the communication from the parent's perspective.
 * It sends the user's request down the pipe and waits for the child's reply.
 */
void parentProcess(int fd[], char *message, Operation choice)
{
    /* the parent only writes to the child and reads the response */
    MY_CLOSE(fd[CHILD_READ]);
    MY_CLOSE(fd[CHILD_WRITE]);

    /*
     * Show the user what will be sent to the child.  The colourful text makes
     * it easy to follow which process is speaking.
     */
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

    /* send the operation code so the child knows how to interpret the data */
    fprintf(stderr, COLOR_WHITE "Parent: " COLOR_RESET "Sending Message to Child Process...\n");

    if (robustWrite(fd[PARENT_WRITE], &choice, sizeof(choice)) != sizeof(choice))
    {
        fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oh dear, I couldn't get your sibling to listen...\n");
        exit(EXIT_FAILURE);
    }

    if (choice != OP_RANDOM_MATH)
    {
        /* send the text the user entered for the child to process */
        MY_SLEEP(delaySeconds);
        if (robustWrite(fd[PARENT_WRITE], message, strlen(message) + 1) != (ssize_t)(strlen(message) + 1))
        {
            fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oopsie daisy, my message got lost in the mail...\n");
            exit(EXIT_FAILURE);
        }
    }

    /* finished sending information */
    MY_CLOSE(fd[PARENT_WRITE]);

    // Wait for and display the modified message or result from the child
    if (choice == OP_RANDOM_MATH)
    {
        /* child sent back a single integer result */
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
        /* otherwise read back the modified string */
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

    /* we have our response; close the pipe */
    MY_CLOSE(fd[PARENT_READ]);
    // The main function will handle waiting for the child
    // wait(NULL); // Wait for the child process to terminate
}
