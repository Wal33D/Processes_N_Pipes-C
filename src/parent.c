#include "utilities.h"

void parentProcess(int fd[], char *message, int choice) {
    char buffer[1024];
    close(fd[CHILD_READ]);
    close(fd[CHILD_WRITE]);

    // A playful message for sending the operation to the child
    switch(choice) {
        case 1:
            printf(COLOR_GREEN "Parent whispers: " COLOR_RESET "Hey sweetie, can you " COLOR_YELLOW "toggle" COLOR_RESET " this for me? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
            break;
        case 2:
            printf(COLOR_GREEN "Parent muses: " COLOR_RESET "Darling, could you please " COLOR_YELLOW "shout" COLOR_RESET " this out loud? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
            break;
        case 3:
            printf(COLOR_GREEN "Parent ponders: " COLOR_RESET "Oh, what if we made this " COLOR_YELLOW "mirror" COLOR_RESET " itself? --> '" COLOR_WHITE "%s" COLOR_RESET "'\n", message);
            break;
        default:
            printf(COLOR_GREEN "Parent is confused: " COLOR_RESET "Hmm, not sure what you want, but let's try '" COLOR_WHITE "%s" COLOR_RESET "' anyway.\n", message);
            break;
    }

    // Send the operation code to the child
    if (write(fd[PARENT_WRITE], &choice, sizeof(choice)) != sizeof(choice)) {
        fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oh dear, I couldn't get your sibling to listen...\n");
        exit(EXIT_FAILURE);
    }

    // Send the message
    if (write(fd[PARENT_WRITE], message, strlen(message) + 1) != strlen(message) + 1) {
        fprintf(stderr, COLOR_WHITE "Parent sighs: " COLOR_RESET "Oopsie daisy, my message got lost in the mail...\n");
        exit(EXIT_FAILURE);
    }

    // Wait for the modified message from the child
    int length = read(fd[PARENT_READ], buffer, sizeof(buffer));
    if (length < 0) {
        fprintf(stderr, COLOR_WHITE "Parent frets: " COLOR_RESET "Gosh, I never heard back. Are they ignoring me?\n");
        exit(EXIT_FAILURE);
    }
    buffer[length] = '\0';

    // Delighted response from the parent
    printf(COLOR_GREEN "Parent beams proudly: " COLOR_RESET "Oh, look at what my clever child did! --> '" COLOR_WHITE "%s" COLOR_YELLOW "'\n", buffer);

    close(fd[PARENT_READ]);
    close(fd[PARENT_WRITE]);
    wait(NULL);
}
