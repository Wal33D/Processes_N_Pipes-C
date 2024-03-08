#include "utilities.h"

int main()
{
    int choice;
    char message[1024];

    printf("Choose a Demo:\n");
    printf("1. Toggle and Return a Message\n");
    printf("2. Uppercase and Return a Message\n");
    printf("3. Palindrome and Return a Message\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    getchar(); // consume the newline character after the number

    if (choice < 1 || choice > 3)
    {
        printf("Invalid choice.\n");
        return 1;
    }

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    int fd[2 * PIPE_PAIRS];
    pid_t pid;

    // Initialize pipes and fork process
    for (int i = 0; i < PIPE_PAIRS; ++i)
    {
        if (pipe(fd + (i * 2)) < 0)
        {
            perror("Pipe initialization failed");
            exit(EXIT_FAILURE);
        }
    }

    pid = fork();
    if (pid < 0)
    {
        perror("Failed to fork process");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    { // Child process
        childProcess(fd, choice);
    }
    else
    { // Parent process
        parentProcess(fd, message, choice);
    }

    return 0;
}
