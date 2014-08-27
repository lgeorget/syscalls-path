#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>

int main(void)
{
	char filename[] = "to_be_linked_XXXXXX";
	printf("Création d'un fichier temporaire\n");
	int fd = mkstemp(filename);
	if (fd < 0) {
		perror("Impossible de créer le fichier temporaire à lier");
		exit(1);
	}
	close(fd);
	
	printf("Lien du fichier \"%s\" vers le nouveau nom \"%s\"\n", filename, "linked");
	int ret = syscall(__NR_link, filename, "linked");
	if (ret < 0) {
		perror("link(2)");
		exit(2);
	}
	
	return 0;
}
