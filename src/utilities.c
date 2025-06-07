#include "utilities.h"

char *toggleString(const char *input)
{
    char *toggledStr = malloc(strlen(input) + 1);
    if (!toggledStr)
    {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; input[i] != '\0'; ++i)
    {
        toggledStr[i] = islower(input[i]) ? toupper(input[i]) : tolower(input[i]);
    }
    toggledStr[strlen(input)] = '\0';

    return toggledStr;
}


char *createPalindrome(const char *word)
{
    if (word == NULL)
        return NULL;

    int len = strlen(word);
    int adjustment = len % 2 == 0 ? 1 : 0;
    char *palindrome = (char *)malloc((len * 2) - adjustment + 1);
    if (!palindrome)
    {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    memcpy(palindrome, word, len);

    for (int i = 0; i < len - adjustment; i++)
    {
        palindrome[len + i] = word[len - i - 1 - adjustment];
    }

    palindrome[(len * 2) - adjustment] = '\0';

    return palindrome;
}

char *uppercaseOperation(const char *input)
{
    if (input == NULL)
        return NULL;

    char *output = malloc(strlen(input) + 1);
    if (!output)
    {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; input[i] != '\0'; ++i)
    {
        output[i] = toupper(input[i]);
    }

    output[strlen(input)] = '\0';

    return output;
}
