#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = popen("printf '2\nHello\n5\n' | ./build/processes-n-pipes", "r");
    if (!fp)
    {
        perror("popen");
        return 1;
    }

    char buffer[2048];
    size_t len = fread(buffer, 1, sizeof(buffer) - 1, fp);
    buffer[len] = '\0';
    pclose(fp);

    if (strstr(buffer, "HELLO") == NULL)
    {
        fprintf(stderr, "Uppercase result not found in output\n");
        return 1;
    }

    printf("Menu test passed.\n");
    return 0;
}
