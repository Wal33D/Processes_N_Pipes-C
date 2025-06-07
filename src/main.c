#include "utilities.h"

/*
 * main.c - Entry point for the Processes-N-Pipes demo program.
 *
 * The program presents a simple text menu that allows the user to
 * choose different inter-process communication (IPC) demonstrations.
 * Depending on the selected option, the parent and child processes
 * exchange messages through pipes and perform various transformations
 * or calculations.  Additional comments throughout the code explain
 * each step so the flow of data can be easily followed.
 */

// Global variable definition for delay duration
int delaySeconds = DEFAULT_DELAY;

int main(int argc, char *argv[])
{
    int choice;
    char message[1024];

    /*
     * Allow an optional command line argument that specifies the
     * number of seconds the parent and child will pause before
     * sending data to one another.  This makes it easy to observe
     * how the processes behave when communication is delayed.
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

    do
    {
        /* Display the available demonstrations on each iteration. */
        printf("\nChoose a Demo:\n\n");
        printf("1. Toggle and Return a Message\n");
        printf("2. Uppercase and Return a Message\n");
        printf("3. Palindrome and Return a Message\n");
        printf("4. Perform a Random Math Operation on a Number\n");
        printf("5. Exit\n");
        /* Read and validate the user's menu selection.  Because fgets
         * reads a whole line including the trailing newline, we parse
         * the string using strtol and check for conversion errors.
         */
        char input[8];
        char *endptr;
        do
        {
            printf("\nEnter your choice (1-5): ");
            /* Prompt for and read the selection line.  If fgets fails we
             * simply restart the loop so the user can try again. */
            if (!fgets(input, sizeof(input), stdin))
            {
                fprintf(stderr, "Error reading input.\n");
                continue;
            }

            long val = strtol(input, &endptr, 10);

            /* strtol provides robust error checking.  endptr will point
             * to the first invalid character; valid choices are the
             * integers 1-5. */
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

        /*
         * Set up two pipes: one pair for parent-to-child
         * communication and one for child-to-parent.  The array
         * contains four file descriptors as defined by the macros in
         * utilities.h.
         */
        int fd[2 * PIPE_PAIRS];
        pid_t pid;

        for (int i = 0; i < PIPE_PAIRS; ++i)
        {
            if (MY_PIPE(fd + (i * 2)) < 0)
            {
                perror("Pipe initialization failed");
                exit(EXIT_FAILURE);
            }
        }

        /* Create the child process.  After fork both parent and child
         * continue executing from this point with different return
         * values. */
        pid = MY_FORK();
        if (pid < 0)
        {
            perror("Failed to fork process");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            /* Child process: perform the selected operation and
             * return the result to the parent through the pipes. */
            childProcess(fd, (Operation)choice);
            exit(0);
        }
        else
        {
            /* Parent process: gather input and forward it to the child. */
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
            /* Wait for the child process to finish before showing the menu
             * again. */
            wait(NULL);
        }
    /* Loop until the user chooses to exit from the menu. */
    } while (choice != 5);

    /* Successful termination. */
    return 0;
}
