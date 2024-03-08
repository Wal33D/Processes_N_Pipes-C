#include "utilities.h"

char *toggleString(const char *input) {
    char *toggledStr = malloc(strlen(input) + 1);
    if (!toggledStr) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; input[i] != '\0'; ++i) {
        toggledStr[i] = islower(input[i]) ? toupper(input[i]) : tolower(input[i]);
    }
    toggledStr[strlen(input)] = '\0';

    return toggledStr;
}

int inputValidation(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <'Your string here'>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 0; argv[1][i] != '\0'; ++i) {
        if (isalpha(argv[1][i])) {
            return 0;
        }
    }

    printf("The string you entered does not contain any alphabetical characters.\n");
    printf("Please run the program again with at least one alphabetical character.\n");
    return EXIT_FAILURE;
}

char *createPalindrome(const char *word) {
    if (word == NULL) return NULL;

    int len = strlen(word);
    int adjustment = len % 2 == 0 ? 1 : 0;
    char *palindrome = (char *)malloc((len * 2) - adjustment + 1);
    if (!palindrome) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    memcpy(palindrome, word, len);

    for (int i = 0; i < len - adjustment; i++) {
        palindrome[len + i] = word[len - i - 1 - adjustment];
    }

    palindrome[(len * 2) - adjustment] = '\0';

    return palindrome;
}

char *uppercaseOperation(const char *input) {
    if (input == NULL) return NULL;

    char *output = malloc(strlen(input) + 1);
    if (!output) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; input[i] != '\0'; ++i) {
        output[i] = toupper(input[i]);
    }

    output[strlen(input)] = '\0';

    return output;
}
