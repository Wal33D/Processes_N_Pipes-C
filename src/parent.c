#include "utilities.h"

void parentProcess(int fd[], char *message, int choice)
{
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

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
        int *pNumber = (int *)message;
        printf(COLOR_GREEN "Parent quizzes: " COLOR_RESET "I wonder how we can play with the number " COLOR_YELLOW "%d" COLOR_RESET " today?\n", *pNumber);
        write(fd[PARENT_WRITE], pNumber, sizeof(int));
        break;
    default:
        printf(COLOR_GREEN "Parent is confused: " COLOR_RESET "Hmm, not sure what you want, but let's try '" COLOR_WHITE "%s" COLOR_RESET "' anyway.\n", message);
        break;
    }

    if (write(fd[PARENT_WRITE], &choice, sizeof(choice)) != sizeof(choice))
    {
        fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oh dear, I couldn't get your sibling to listen...\n");
        exit(EXIT_FAILURE);
    }

    if (choice != 4)
    {
        if (write(fd[PARENT_WRITE], message, strlen(message) + 1) != strlen(message) + 1)
        {
            fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oopsie daisy, my message got lost in the mail...\n");
            exit(EXIT_FAILURE);
        }
    }

    char buffer[1024];
    int length;
    if (choice == 4)
    {
        int result;
        if ((length = read(fd[PARENT_READ], &result, sizeof(result))) < 0)
        {
            fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Gosh, I never heard back. Are they ignoring me?\n");
            exit(EXIT_FAILURE);
        }
        printf(COLOR_GREEN "Parent beams proudly: " COLOR_RESET "Look! The number magic turned it into " COLOR_YELLOW "%d" COLOR_RESET "!\n", result);
    }
    else
    {
        if ((length = read(fd[PARENT_READ], buffer, sizeof(buffer) - 1)) < 0)
        {
            fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Gosh, I never heard back. Are they ignoring me?\n");
            exit(EXIT_FAILURE);
        }
        buffer[length] = '\0';
        printf(COLOR_GREEN "Parent beams proudly: " COLOR_RESET "Oh, look at what my clever child did! --> '" COLOR_YELLOW "%s" COLOR_RESET "'\n", buffer);
    }

    char thankYouMsg[] = "Thanks for talking, kiddo!";
    write(fd[PARENT_WRITE], thankYouMsg, sizeof(thankYouMsg));

    if ((length = read(fd[PARENT_READ], buffer, sizeof(buffer) - 1)) < 0)
    {
        fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Seems I can't hear back from my child.\n");
        exit(EXIT_FAILURE);
    }
    buffer[length] = '\0';
    printf(COLOR_GREEN "Parent smiles warmly: " COLOR_RESET "%s\n", buffer);

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL);
}
