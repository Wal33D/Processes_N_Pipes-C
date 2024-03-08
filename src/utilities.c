#include "utilities.h"

// Toggles the case of each character in the input string.
 
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

// Validates the command line input to ensure there is exactly one argument provided
// and that it contains at least one alphabetical character.
 
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

void createPalindrome(char *word) {
    int len = strlen(word);
    int adjustment = (len % 2 == 0) ? 1 : 0;
    char palindrome[(len * 2) - adjustment + 1];
    strcpy(palindrome, word);

    for (int i = 0; i < len - adjustment; i++) {
        palindrome[len + i] = word[len - i - 1 - adjustment];
    }

    palindrome[(len * 2) - adjustment] = '\0';
    printf("Palindrome: %s\n", palindrome);
}


char *uppercaseOperation(const char *input) {
    if (input == NULL) return NULL;

    // Allocate memory for the new string
    char *output = malloc(strlen(input) + 1); // +1 for the null terminator
    if (!output) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    // Convert each character to uppercase
    for (int i = 0; input[i] != '\0'; ++i) {
        output[i] = toupper(input[i]);
    }

    // Null-terminate the new string
    output[strlen(input)] = '\0';

    return output;
}