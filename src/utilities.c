#include "utilities.h"
#include <errno.h>

ssize_t robustRead(int fd, void *buf, size_t count)
{
    size_t total = 0;
    char *ptr = buf;

    while (total < count)
    {
        ssize_t n = MY_READ(fd, ptr + total, count - total);
        if (n < 0)
        {
            if (errno == EINTR)
                continue;
            perror("Read failed");
            return -1;
        }
        if (n == 0)
            break; /* EOF */
        total += n;
    }

    return (ssize_t)total;
}

ssize_t robustWrite(int fd, const void *buf, size_t count)
{
    size_t total = 0;
    const char *ptr = buf;

    while (total < count)
    {
        ssize_t n = MY_WRITE(fd, ptr + total, count - total);
        if (n <= 0)
        {
            if (n < 0 && errno == EINTR)
                continue;
            perror("Write failed");
            return -1;
        }
        total += n;
    }

    return (ssize_t)total;
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
    /*
     * The palindrome should mirror the string without repeating the
     * last character.  Therefore, only len - 1 characters are appended
     * to the original word when constructing the palindrome.
     */
    char *palindrome = malloc((len * 2) - 1 + 1); /* original + reverse without last + null */
    if (!palindrome)
    {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    /* Copy the original word */
    memcpy(palindrome, word, len);

    /* Append the reverse of the word excluding the last character */
    for (int i = 0; i < len - 1; ++i)
    {
        palindrome[len + i] = word[len - 2 - i];
    }

    palindrome[(len * 2) - 1] = '\0';

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
