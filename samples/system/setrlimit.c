#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(void)
{
	printf("Essayons d'augmenter le nombre de descripteurs de fichiers disponibles à 2048 (limite souple) et 4096 (limite stricte)...\n");

	struct rlimit max_fds = { 2048, 4096 };
	int ret = syscall(__NR_setrlimit, RLIMIT_NOFILE, &max_fds);
	if (ret < 0) {
		perror("On ne peut pas");
		exit(1);
	}

	printf("C'est fait !\n");
	return 0;
}
