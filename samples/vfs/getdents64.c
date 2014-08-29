#define _GNU_SOURCE
#include <dirent.h>     /* Définie les constantes DT_* */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <inttypes.h>

struct linux_dirent64 {
	uint64_t       d_ino;
	int64_t        d_off;
	unsigned short d_reclen;
	unsigned char  d_type;
	char           d_name[];
};

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
	int fd, nread;
	char buf[BUF_SIZE];
	struct linux_dirent64 *d;
	int bpos;

	fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
	if (fd == -1) {
		perror("Impossible d'ouvrir le répertoire courant");
		exit(1);
	}

	nread = syscall(__NR_getdents64, fd, buf, BUF_SIZE);
	if (nread == -1) {
		perror("getdents64(2)");
		exit(2);
	}

	printf("--------------- nread=%d ---------------\n", nread);
	printf("i-node#  file type  d_reclen  d_off   d_name\n");
	for (bpos = 0; bpos < nread;) {
		d = (struct linux_dirent64 *) (buf + bpos);
		printf("%8"PRIu64" ", d->d_ino);
		printf("%-10s ", (d->d_type == DT_REG) ? "regular" :
				(d->d_type == DT_DIR) ? "directory" :
				(d->d_type == DT_FIFO) ? "FIFO" :
				(d->d_type == DT_SOCK) ? "socket" :
				(d->d_type == DT_LNK) ? "symlink" :
				(d->d_type == DT_BLK) ? "block dev" :
				(d->d_type == DT_CHR) ? "char dev" : "???");
		printf("%4d %10"PRId64"  %s\n", d->d_reclen,
				(int64_t) d->d_off, d->d_name);
		bpos += d->d_reclen;
	}

	return 0;
}
