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
	struct rusage usage;

	int r = syscall(__NR_getrusage, RUSAGE_SELF, &usage);
	if (r < 0) {
		int err = errno;
		perror("System call getrusage failed");
		exit(err);
	}

	printf(	"Temps total passé en mode utilisateur : %li,%06lis\n"
		"Temps total passé en mode noyau : %li,%06lis\n"
		"Taille maximale de mémoire résidente utilisée : %li\n"
		"Nombre de fautes de pages qui ont été corrigées par une simple réallocation de pages en attente de nettoyage : %li\n"
		"Nombre de fautes de pages qui ont nécessité une entrée--sortie pour être corrigées : %li\n"
		"Nombre de fois que le système de fichiers a réalisé une lecture : %li\n"
		"Nombre de fois que le système de fichiers a réalisé une écriture : %li\n"
		"Nombre de changements de contexte provoqués par le programme lui-même : %li\n"
		"Nombre de changements de contexte provoqués par le système : %li\n",
		usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
		usage.ru_stime.tv_sec, usage.ru_utime.tv_usec, 
		usage.ru_maxrss, usage.ru_minflt, usage.ru_majflt,
		usage.ru_inblock, usage.ru_oublock,
		usage.ru_nvcsw, usage.ru_nivcsw);
}
