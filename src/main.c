#include "utilities.h"

int main()
{
    int choice;
    char message[1024];

    do
    {
        printf("\nChoose a Demo:\n\n");
        printf("1. Toggle and Return a Message\n");
        printf("2. Uppercase and Return a Message\n");
        printf("3. Palindrome and Return a Message\n");
        printf("4. Perform a Random Math Operation on a Number\n");
        printf("5. Exit\n");
        printf("\nEnter your choice (1-5): ");
        scanf("%d", &choice);
        getchar();

        if (choice == 5)
        {
            printf("Exiting...\n");
            break;
        }

        int fd[2 * PIPE_PAIRS];
        pid_t pid;

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
        {
            childProcess(fd, choice);
            exit(0);
        }
        else
        {
            if (choice == 4)
            {
                int number;
                printf(COLOR_GREEN "Parent asks: " COLOR_RESET "Enter a number: ");
                scanf("%d", &number);
                parentProcess(fd, (char *)&number, choice);
            }
            else
            {
                printf(COLOR_GREEN "Parent asks: " COLOR_RESET "Enter your message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                parentProcess(fd, message, choice);
            }
            wait(NULL);
        }
    } while (choice != 5);

    return 0;
}
