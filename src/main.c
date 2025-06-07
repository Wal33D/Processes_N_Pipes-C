#include "utilities.h"

/*
 * Communication delay between the parent and child processes.  This value can
 * be overridden via the command line to demonstrate how timing affects pipe
 * based IPC.
 */
int delaySeconds = DEFAULT_DELAY;

/*
 * Entry point of the demo.  Presents a menu to the user, spawns a child
 * process and showcases several forms of IPC using pipes.
 */
int main(int argc, char *argv[])
{
    int choice;
    char message[1024];

    /*
     * The first command line argument, if provided, overrides the default
     * communication delay.  This lets the user experiment with different
     * timings when running the demo.
     */
    if (argc >= 2)
    {
        char *endptr = NULL;
        long val = strtol(argv[1], &endptr, 10);

        if (*argv[1] != '\0' && *endptr == '\0' && val >= 0)
        {
            delaySeconds = (int)val;
        }
        else
        {
            fprintf(stderr, "Invalid numeric delay. Using default of %d seconds.\n", DEFAULT_DELAY);
        }
    }

    /* Interactive menu loop.  The program continues until the user chooses
     * the Exit option. */
    do
    {
        printf("\nChoose a Demo:\n\n");
        printf("1. Toggle and Return a Message\n");
        printf("2. Uppercase and Return a Message\n");
        printf("3. Palindrome and Return a Message\n");
        printf("4. Perform a Random Math Operation on a Number\n");
        printf("5. Exit\n");
        char input[8];
        char *endptr;
        /* keep prompting until we get a valid menu selection */
        do
        {
            printf("\nEnter your choice (1-5): ");
            if (!fgets(input, sizeof(input), stdin))
            {
                fprintf(stderr, "Error reading input.\n");
                continue;
            }

            long val = strtol(input, &endptr, 10);

            if (endptr == input || (*endptr != '\n' && *endptr != '\0') || val < 1 || val > 5)
            {
                printf("Invalid choice. Please try again.\n");
            }
            else
            {
                choice = (int)val;
                break;
            }
        } while (1);

        if (choice == 5)
        {
            printf("Exiting...\n");
            break;
        }

        int fd[2 * PIPE_PAIRS];
        pid_t pid;

        /* create the two pipes used for bi-directional communication */
        for (int i = 0; i < PIPE_PAIRS; ++i)
        {
            if (MY_PIPE(fd + (i * 2)) < 0)
            {
                perror("Pipe initialization failed");
                exit(EXIT_FAILURE);
            }
        }

        /* split into parent and child processes */
        pid = MY_FORK();
        if (pid < 0)
        {
            perror("Failed to fork process");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            /* child: perform the requested operation */
            childProcess(fd, (Operation)choice);
            exit(0);
        }
        else
        {
            /* parent: gather input and send it to the child */
            if (choice == OP_RANDOM_MATH)
            {
                int number;
                printf(COLOR_GREEN "Parent asks: " COLOR_RESET "Enter a number: ");
                scanf("%d", &number);
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                parentProcess(fd, (char *)&number, (Operation)choice);
            }
            else
            {
                printf(COLOR_GREEN "Parent asks: " COLOR_RESET "Enter your message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                parentProcess(fd, message, (Operation)choice);
            }
            /* wait for the child to finish before showing the menu again */
            wait(NULL);
        }
    } while (choice != 5);

    return 0;
}
