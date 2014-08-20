#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#include <sys/utsname.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	struct utsname info;

	int r = syscall(__NR_uname, &info);
	if (r < 0) {
		int err = errno;
		perror("System call sysinfo failed");
		exit(err);
	}

	printf(
		"Nom du noyau : %s\n"
		"Nom du nœud : %s\n"
		"Version du système d'exploitation : %s\n"
		"Information de révision du noyau : %s\n"
		"Architecture : %s\n"
		"Nom de domaine NIS ou YP : %s\n",
		info.sysname, info.nodename, info.release, info.version,
		info.machine, info.domainname);
}
