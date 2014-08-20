#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#include <sys/sysinfo.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	struct sysinfo info;

	int r = syscall(__NR_sysinfo, &info);
	if (r < 0) {
		int err = errno;
		perror("System call sysinfo failed");
		exit(err);
	}

	printf(
		"Nombre de secondes écoulées depuis le démarrage du système : \
		%li\n"
		"Charge du système pour \n\tla minute passée : %lu \
					\n\tles cinq dernières minutes : %lu \
					\n\tles quinze dernières minutes : %lu\
					\n"
		"Mémoire totale du système : %lu o\n"
		"Mémoire disponible dans le système : %lu o\n"
		"Mémoire partagée dans le système : %lu o\n"
		"Mémoire utilisée par les tampons : %lu o\n",
		info.uptime, info.loads[0], info.loads[1], info.loads[2],
		info.totalram, info.freeram, info.sharedram, info.bufferram);
	printf(
		"Taille totale de l'espace d'échange : %lu o\n"
		"Taille totale de l'espace d'échange inoccupé : %lu o\n"
		"Nombre de processus en exécution : %hu\n"
		"Mémoire adressable par les processus totale : %lu o\n"
		"Mémoire adressable par les processus disponible : %lu o\n"
		"Taille du bloc mémoire unitaire : %u o\n",
		info.totalswap, info.freeswap, info.procs, info.totalhigh,
		info.freehigh, info.mem_unit);
}
