#include "utilities.h"

ssize_t robustRead(int fd, void *buf, size_t count)
{
    ssize_t n = MY_READ(fd, buf, count);
    if (n < 0)
    {
        perror("Read failed");
        return -1;
    }
    return n;
}

ssize_t robustWrite(int fd, const void *buf, size_t count)
{
    ssize_t n = MY_WRITE(fd, buf, count);
    if (n < 0)
    {
        perror("Write failed");
        return -1;
    }
    return n;
}

char *toggleString(const char *input)
{
    size_t len = strlen(input);
    char *toggledStr = malloc(len + 1);
    if (!toggledStr)
    {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < len; ++i)
    {
        toggledStr[i] = islower((unsigned char)input[i]) ? toupper((unsigned char)input[i]) : tolower((unsigned char)input[i]);
    }
    toggledStr[len] = '\0';

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

    size_t len = strlen(input);
    char *output = malloc(len + 1);
    if (!output)
    {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < len; ++i)
    {
        output[i] = toupper((unsigned char)input[i]);
    }

    output[len] = '\0';

    return output;
}

int randomMathOperation(int number)
{
    int operationNumber = rand() % 10;
    switch (rand() % 3)
    {
    case 0:
        number += operationNumber;
        break;
    case 1:
        number -= operationNumber;
        break;
    case 2:
        operationNumber = (rand() % 3) + 1;
        number *= operationNumber;
        break;
    }
    return number;
}
