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
    fprintf(stderr, "Teeing %i bytes from standard input to standard output, both must be pipes...\n", NB_BYTES);

    int r = syscall(__NR_tee, 0, 1, NB_BYTES, 0);
    if (r < 0) {
	int err = errno;
	perror("System call tee failed");
	exit(err);
    }
}
