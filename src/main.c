#include "utilities.h"

// Main function
int main() {
    int choice;
    char message[1024]; // Assuming a message limit of 1024 characters

    printf("Choose a Demo:\n");
    printf("1. Toggle and Return a Message\n");
    printf("2. Uppercase and Return a Message\n");
    printf("3. Palindrome and Return a Message\n");
    printf("4. Simulated Message Exchange - not done\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);
    getchar(); // consume the newline character after the number

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

    pid = fork();
    if (pid < 0) {
        perror("Failed to fork process");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Assuming the childProcess now decides which operation to perform based on `choice`
        childProcess(fd, choice);
    } else { // Parent process
        parentProcess(fd, message);
    }

    return 0;
}