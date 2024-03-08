#include "utilities.h"

int main()
{
    int choice;
    char message[1024]; // Used for string operations and reading numbers as strings

    printf("Choose a Demo:\n");
    printf("1. Toggle and Return a Message\n");
    printf("2. Uppercase and Return a Message\n");
    printf("3. Palindrome and Return a Message\n");
    printf("4. Perform a Random Math Operation on a Number\n"); // New option
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);
    getchar(); // consume the newline character after the number

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
        if (choice == 4)
        {
            int number;
            printf(COLOR_GREEN "Parent asks: " COLOR_RESET "Enter a number: ");
            scanf("%d", &number);
            // Casting number as char* for compatibility
            parentProcess(fd, (char *)&number, choice);
        }
        else
        {
            printf(COLOR_GREEN "Parent asks: " COLOR_RESET "Enter your message: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = 0; // Remove the newline character at the end
            parentProcess(fd, message, choice);
        }
    }

    return 0;
}
