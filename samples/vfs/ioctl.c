#define _GNU_SESSION

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/cdrom.h>

#include <sys/syscall.h>
#include <unistd.h>

int main(void)
{
	printf("Éjection du CDROM...\n");

	int fd = open("/dev/sr0", O_RDWR|O_NONBLOCK);
	if (fd < 0) {
		perror("Impossible d'ouvrir le fichier /dev/sr0");
		exit(1);
	}

	if (syscall(__NR_ioctl, fd, CDROMEJECT) < 0)
		perror("Éjection échouée");

	close(fd);
	return 0;
}
