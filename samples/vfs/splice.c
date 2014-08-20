#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#define NB_BYTES 10

int main(void)
{
    fprintf(stderr, "Splicing %i bytes from standard input which must be a pipe to standard output...\n", NB_BYTES);

    int r = syscall(__NR_splice, 0, NULL, 1, NULL, NB_BYTES, 0);
    if (r < 0) {
	int err = errno;
	perror("System call splice failed");
	exit(err);
    }
}
