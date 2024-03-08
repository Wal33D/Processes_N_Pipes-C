#include "utilities.h"

/**
 * Toggles the case of each character in the input string.
 * 
 * @param input The input string whose case is to be toggled.
 * @return A new string with each character's case toggled.
 */
char *toggleString(const char *input) {
    // Allocate memory for the toggled string including the null terminator
    char *toggledStr = malloc(strlen(input) + 1);
    if (!toggledStr) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; input[i] != '\0'; ++i) {
        toggledStr[i] = islower(input[i]) ? toupper(input[i]) : tolower(input[i]);
    }
    toggledStr[strlen(input)] = '\0'; // Ensure string is null-terminated

    return toggledStr;
}

/**
 * Validates the command line input to ensure there is exactly one argument provided
 * and that it contains at least one alphabetical character.
 * 
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return 0 if the input is valid, EXIT_FAILURE otherwise.
 */
int inputValidation(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <'Your string here'>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Check if the input contains at least one alphabetical character
    for (int i = 0; argv[1][i] != '\0'; ++i) {
        if (isalpha(argv[1][i])) {
            return 0; // Valid input
        }
    }

    // No alphabetical characters found
    printf("The string you entered does not contain any alphabetical characters.\n");
    printf("Please run the program again with at least one alphabetical character.\n");
    return EXIT_FAILURE;
}

