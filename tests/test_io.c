#include "utilities.h"
#include <string.h>
#include <assert.h>

int main(void) {
    int fd[2];
    if (MY_PIPE(fd) < 0) {
        perror("pipe");
        return 1;
    }

    const size_t len = 8192;
    char *sendbuf = malloc(len);
    char *recvbuf = malloc(len);
    if (!sendbuf || !recvbuf) {
        perror("malloc");
        return 1;
    }
    for (size_t i = 0; i < len; ++i) sendbuf[i] = (char)('A' + (i % 26));

    ssize_t w = robustWrite(fd[1], sendbuf, len);
    assert(w == (ssize_t)len);
    MY_CLOSE(fd[1]);

    ssize_t r = robustRead(fd[0], recvbuf, len);
    assert(r == (ssize_t)len);
    assert(memcmp(sendbuf, recvbuf, len) == 0);
    MY_CLOSE(fd[0]);

    free(sendbuf);
    free(recvbuf);
    printf("IO test passed.\n");
    return 0;
}
