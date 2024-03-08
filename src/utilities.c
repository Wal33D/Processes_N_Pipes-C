#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <ctype.h>
#include "utilities.h"

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
