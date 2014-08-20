#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#define NB_BYTES 5

int main(void)
{
    printf("Reading %i bytes from standard input...\n", NB_BYTES-1);

    char buffer[NB_BYTES];
/*    int r = syscall(__NR_read, 0, buffer, NB_BYTES-1);*/
	long int r;

	asm("mov $0, %rdi");
	asm("movq %0, %%rsi"
			:: "q" (buffer));
	asm("mov $0, %rax");
	asm("movq $4, %rdx");
	asm("syscall");
	asm("movq %%rax, %0"
			: "=q" (r));

	if (r < 0) {
		int err = errno;
		perror("System call read failed");
		exit(err);
	}

    buffer[r] = 0;
    printf("Read from standard input : \n\n%s\n", buffer);
    exit(0);
}
