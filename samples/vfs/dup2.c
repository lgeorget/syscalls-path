#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	fprintf(stderr, "Duplicating the standard output on the error output...\n");

	int r = syscall(__NR_dup2, 1, 2);
	if (r < 0) {
		int err = errno;
		perror("System call dup2 failed");
		exit(err);
	}
}
