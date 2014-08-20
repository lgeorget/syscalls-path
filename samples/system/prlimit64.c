#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#include <sys/time.h>
#include <sys/resource.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	struct rlimit new_fork_limit = { 4, 6 };
	struct rlimit old_fork_limit;

	int r = syscall(__NR_prlimit64, 0, RLIMIT_NPROC, &new_fork_limit, &old_fork_limit);

	if (r < 0) {
		int err = errno;
		perror("System call prlimit failed");
		exit(err);
	}

	printf("Number of allowed forks changed to (soft limit: 4, "
		"hard limit: 6). Previous value was (soft limit: %li, "
		"hard limit: %li).",
		old_fork_limit.rlim_cur, old_fork_limit.rlim_max);
}
