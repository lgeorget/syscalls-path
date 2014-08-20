#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	unsigned int cpu;
	unsigned int node;

	int r = syscall(__NR_getcpu, &cpu, &node, NULL);

	if (r < 0) {
		int err = errno;
		perror("System call getcpu failed");
		exit(err);
	}

	printf("Current process executed on CPU %u and NUMA node %u when the "
		"system call was made\n", cpu, node);
}
