#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(void)
{
	printf("Combien de descripteurs de fichiers puis-je ouvrir ?\n");

	struct rlimit max_fds;
	int ret = syscall(__NR_getrlimit, RLIMIT_NOFILE, &max_fds);
	if (ret < 0) {
		perror("On ne saura pas");
		exit(1);
	}

	printf("Limite souple : %i\nLimite stricte : %i\n", 
			max_fds.rlim_cur, max_fds.rlim_max);
	return 0;
}
