#include "utilities.h"

void parentProcess(int fd[], char *message, int choice)
{
    // Close the pipe ends that are not used by the parent
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    // Send different messages based on the choice of operation
    switch (choice)
    {
    case 1:
        // Request to toggle the case of the message
        printf(COLOR_GREEN "Parent whispers: " COLOR_RESET "Hey sweetie, can you " COLOR_YELLOW "toggle" COLOR_RESET " this for me? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case 2:
        // Request to convert the message to uppercase
        printf(COLOR_GREEN "Parent muses: " COLOR_RESET "Darling, could you please " COLOR_YELLOW "shout" COLOR_RESET " this out loud? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case 3:
        // Request to convert the message to a palindrome
        printf(COLOR_GREEN "Parent ponders: " COLOR_RESET "Oh, what if we made this " COLOR_YELLOW "mirror" COLOR_RESET " itself? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
        break;
    case 4:
        // Request a random math operation on a number
        int *pNumber = (int *)message;
        printf(COLOR_GREEN "Parent quizzes: " COLOR_RESET "I wonder how we can play with the number " COLOR_YELLOW "%d" COLOR_RESET " today?\n", *pNumber);
        write(fd[PARENT_WRITE], pNumber, sizeof(int));
        break;
    default:
        // Fallback message for unrecognized choice
        printf(COLOR_GREEN "Parent is confused: " COLOR_RESET "Hmm, not sure what you want, but let's try '" COLOR_WHITE "%s" COLOR_RESET "' anyway.\n", message);
        break;
    }

    // Send the operation code to the child process
    if (write(fd[PARENT_WRITE], &choice, sizeof(choice)) != sizeof(choice))
    {
        fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oh dear, I couldn't get your sibling to listen...\n");
        exit(EXIT_FAILURE);
    }

    // If not performing a math operation, send the message to the child
    if (choice != 4)
    {
        if (write(fd[PARENT_WRITE], message, strlen(message) + 1) != strlen(message) + 1)
        {
            fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oopsie daisy, my message got lost in the mail...\n");
            exit(EXIT_FAILURE);
        }
    }

    // Buffer to store the response from the child process
    char buffer[1024];
    int length;

    // Process the response from the child, either a modified message or a math result
    if (choice == 4)
    {
        int result;
        if ((length = read(fd[PARENT_READ], &result, sizeof(result))) < 0)
        {
            fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Gosh, I never heard back. Are they ignoring me?\n");
            exit(EXIT_FAILURE);
        }
        // Display the result of the math operation
        printf(COLOR_GREEN "Parent beams proudly: " COLOR_RESET "Look! The number magic turned it into " COLOR_YELLOW "%d" COLOR_RESET "!\n", result);
    }
    else
    {
        // Display the modified message
        if ((length = read(fd[PARENT_READ], buffer, sizeof(buffer) - 1)) < 0)
        {
            fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Gosh, I never heard back. Are they ignoring me?\n");
            exit(EXIT_FAILURE);
        }
        buffer[length] = '\0';
        printf(COLOR_GREEN "Parent beams proudly: " COLOR_RESET "Oh, look at what my clever child did! --> '" COLOR_YELLOW "%s" COLOR_RESET "'\n", buffer);
    }

    // Send a thank you message to the child for their work
    char thankYouMsg[] = "Thanks for talking, kiddo!";
    write(fd[PARENT_WRITE], thankYouMsg, sizeof(thankYouMsg));

    // Wait for the child's final response to the thank you message
    if ((length = read(fd[PARENT_READ], buffer, sizeof(buffer) - 1)) < 0)
    {
        fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Seems I can't hear back from my child.\n");
        exit(EXIT_FAILURE);
    }
    buffer[length] = '\0';
    // Display the child's response to the thank you message
    printf(COLOR_GREEN "Parent smiles warmly: " COLOR_RESET "%s\n", buffer);

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL);
}
