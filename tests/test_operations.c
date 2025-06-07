#include "utilities.h"

/* Simple unit tests for the helper functions in utilities.c. */
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main(void) {
    char *res;

    res = toggleString("AbC");
    assert(strcmp(res, "aBc") == 0);
    free(res);

    res = uppercaseOperation("Abc!");
    assert(strcmp(res, "ABC!") == 0);
    free(res);

    res = createPalindrome("abcd");
    assert(strcmp(res, "abcdcba") == 0);
    free(res);

    /* Test odd length palindrome generation */
    res = createPalindrome("abc");
    assert(strcmp(res, "abcba") == 0);
    free(res);

    /* Test single character string */
    res = createPalindrome("a");
    assert(strcmp(res, "a") == 0);
    free(res);

    srand(1);
    int out = randomMathOperation(5);
    assert(out == 2); /* expected value with seed 1 */

    printf("All tests passed.\n");
    return 0;
}
