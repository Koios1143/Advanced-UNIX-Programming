#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FILE_MODE 0644
#define COPYINCR (1024 * 1024l * 1024)

#define err_sys(fmt, ...) fprintf(stderr, (fmt "\n"), ##__VA_ARGS__)
#define err_quit(fmt, ...) do { err_sys(fmt, ##__VA_ARGS__); exit(1); } while(0)

int main(int argc, char *argv[])
{
	int fdin, fdout;
	void *src, *dst;
	size_t copysz;
	struct stat sbuf;
	off_t fsz = 0;

	if (argc != 3)
		err_quit("usage: %s <fromfile> <tofile>", argv[0]);

	if ((fdin = open(argv[1], O_RDONLY)) < 0)
		err_sys("can’t open %s for reading", argv[1]);

	if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
		err_sys("can’t creat %s for writing", argv[2]);

	if (fstat(fdin, &sbuf) < 0)         /* need size of input file */
		err_sys("fstat error");

	if (ftruncate(fdout, sbuf.st_size) < 0) /* set output file size */
		err_sys("ftruncate error");

	while (fsz < sbuf.st_size) {
		if ((sbuf.st_size - fsz) > COPYINCR)
			copysz = COPYINCR;
		else
			copysz = sbuf.st_size - fsz;

		/* TODO: Copy the file using mmap here */
		char *src_buf = mmap(NULL, copysz, PROT_READ, MAP_SHARED, fdin, fsz);
		//close(fdin);
		char *dst_buf = mmap(NULL, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz);
		memcpy(dst_buf, src_buf, copysz);
		fsz += copysz;
	}
	exit(0); 
}
