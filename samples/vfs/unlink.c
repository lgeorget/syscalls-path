#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>

int main(void)
{
	char filename[] = "to_be_destroyed_XXXXXX";
	printf("Création d'un fichier temporaire\n");
	int fd = mkstemp(filename);
	if (fd < 0) {
		perror("Impossible de créer le fichier temporaire à détruire");
		exit(1);
	}
	close(fd);
	
	printf("Destruction du fichier %s\n",filename);
	int ret = syscall(__NR_unlink, filename);
	if (ret < 0) {
		perror("unlink(2)");
		exit(2);
	}
	
	return 0;
}
