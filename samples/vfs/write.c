#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>

int main(void)
{
	const char message[] = "I'm the test message for write(2).\n";
	syscall(__NR_write, STDOUT_FILENO, message, sizeof(message));
	exit(0);
}

