#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>

#include <sys/syscall.h>

int main(void)
{
	struct pollfd fds = { 0, POLLIN, 0 };

	int retval = syscall(__NR_poll, &fds, 1, 5);

	if (retval == -1)
		perror("poll()");
	else if (retval)
		printf("Data is available now.\n");
	else
		printf("No data within five seconds.\n");

	exit(EXIT_SUCCESS);
}
