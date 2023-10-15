#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <flags.c>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct fmemopen_cookie {
    char *buf;      /* pointer to the memory region */
    int   size;     /* buffer length in bytes */
    int   len;      /* data length in bytes */
    int   off;      /* current offset into the buffer */
} fmemopen_cookie_t;

int readfn(void *cookie, char *buf, int nbytes);
int writefn(void *cookie, const char *buf, int nbytes);
fpos_t seekfn(void *cookie, fpos_t offset, int whence);
int closefn(void *cookie);
int __sflags(const char *mode, int *optr);

/*
 * Not supporting 'b' mode because I think it's not 
 * necessary for this assignment
 */
FILE *fmemopen(void *__restrict buf, size_t size, const char *__restrict mode) {
    fmemopen_cookie_t *c;
    FILE *f;
    int flags;

    c = malloc(sizeof(fmemopen_cookie_t));

    c->off = 0;
    c->size = size;
    c->buf = buf;

    if(mode[0] == 'w')
        c->buf[0] = '\0';
    /*
     * The size of the current buffer contents for 'a'
     * mode is the position of the first NULL byte
     * or the size of the buffer if none is found
     */
    if (mode[0] == 'a') {
        c->off = strnlen(c->buf, c->size);
        c->len = strnlen(c->buf, c->size);
    } else if (mode[0] == 'r') {
        c->len = size;
    } else if (mode[0] == 'w') {
        c->len = 0;
    }

    __sflags(mode, &flags);
    f = funopen(c,
        flags & O_WRONLY ? NULL : readfn,
        flags & O_RDONLY ? NULL : writefn,
        seekfn,
        closefn);
    
    return f;
}

int __sflags(const char *mode, int *optr)
{
	int ret, m, o;
	switch (*mode++) {
	case 'r':	/* open for reading */
		ret = __SRD;
		m = O_RDONLY;
		o = 0;
		break;
	case 'w':	/* open for writing */
		ret = __SWR;
		m = O_WRONLY;
		o = O_CREAT | O_TRUNC;
		break;
	case 'a':	/* open for appending */
		ret = __SWR;
		m = O_WRONLY;
		o = O_CREAT | O_APPEND;
		break;
	default:	/* illegal mode */
		return (0);
	}
	/* [rwa]\+ or [rwa]b\+ means read and write */
	if (*mode == '+' || (*mode == 'b' && mode[1] == '+')) {
		ret = __SRW;
		m = O_RDWR;
	}
	*optr = m | o;
	return (ret);
}

int readfn(void *cookie, char *buf, int nbytes) {
    fmemopen_cookie_t *c = (fmemopen_cookie_t *)cookie;
    nbytes = MIN(nbytes, c->len - c->off);
    if (nbytes == 0)
        return 0;
    memcpy(buf, c->buf + c->off, nbytes);
    c->off += nbytes;
    return nbytes;
}

int writefn(void *cookie, const char *buf, int nbytes) {
    fmemopen_cookie_t *c = (fmemopen_cookie_t *)cookie;
    nbytes = MIN(nbytes, c->size - c->off);
    if (nbytes == 0)
        return 0;
    memcpy(c->buf + c->off, buf, nbytes);
    c->off += nbytes;
    /* Keep in mind that offset is not necessarily the 
     * same as length
     */
    c->len = MAX(c->len, c->off);
    /*
     * Append a null byte to the end of the buffer if 
     * all below conditions are met:
     * - the buffer is not full
     * - the data just written doesn't already end with a 
     *   null byte
     */
    if (c->off < c->size && c->buf[c->off - 1] != '\0')
        c->buf[c->off] = '\0';
    return nbytes;
}

fpos_t seekfn(void *cookie, fpos_t offset, int whence) {
    fmemopen_cookie_t *c = (fmemopen_cookie_t *)cookie;
    switch (whence) {
        case SEEK_SET:
            c->off = offset;
            break;
        case SEEK_CUR:
            c->off += offset;
            break;
        case SEEK_END:
            c->off = c->len + offset;
            break;
        default:
            return -1;
    }
    return c->off;
}

int closefn(void *cookie) {
    fmemopen_cookie_t *c = (fmemopen_cookie_t *)cookie;
    free(c);
    return 0;
}

int main(){
    // Write "hello, world" in the file stream
    char *buf = malloc(100);
    FILE *fp = fmemopen(buf, 100, "w+");
    fprintf(fp, "hello, world");

    // Seek the position of "world" in the file stream
    fseek(fp, 7, SEEK_SET);
    
    // Read the world "world" from the file stream and print it.
    char *buf2 = malloc(100);
    fread(buf2, 1, 5, fp);
    printf("%s\n", buf2);
    // Then, print the whole sentence "hello, world".
    fseek(fp, 0, SEEK_SET);
    char *buf3 = malloc(100);
    fread(buf3, 1, 12, fp);
    printf("%s\n", buf3);

    // Close the file stream correctly
    fclose(fp);
    free(buf);
    free(buf2);
    free(buf3);
    return 0;
}