#include "utilities.h"

void demoToggleString(char *input) {
    char *toggledMessage = toggleString(input);
    printf("Toggled message: %s\n", toggledMessage);
    free(toggledMessage);
}


int main() {
    int choice;
    char message[1024]; // Assuming a message limit of 1024 characters

    printf("Choose a Demo:\n");
    printf("1. Toggle and Return a Message\n");
    printf("2. Uppercase and Return a Message\n");
    printf("3. Palindrome and Return a Message\n");
    printf("4. Simulated Message Exchange - not done\n"); // New option
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);
    getchar(); // consume the newline character after the number

    switch (choice) {
        case 1:
        case 2:
            printf("Enter your message: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = 0; // Remove the newline character at the end

            int fd[2 * PIPE_PAIRS];
            pid_t pid;

            for (int i = 0; i < PIPE_PAIRS; ++i) {
                if (pipe(fd + (i * 2)) < 0) {
                    perror("Pipe initialization failed");
                    exit(EXIT_FAILURE);
                }
            }

            if ((pid = fork()) < 0) {
                perror("Failed to fork process");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) { // Child process
                if (choice == 1) {
                    childProcess(fd);
                } else {
                }
            } else { // Parent process
                if (choice == 1) {
                    parentProcess(fd, message);
                } else {
                }
            }
            break;

        case 3:
            printf("Enter your message: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = 0; // Remove the newline character at the end
            demoToggleString(message);
            break;

        case 4: // New case for creating a palindrome
            printf("Enter a word to create its palindrome: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = 0; // Remove the newline character at the end
            createPalindrome(message);
            break;

        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
