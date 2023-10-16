#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MIN(a, b) ((a<b) ? a : b)
#define MAX(a, b) ((a>b) ? a : b)
typedef struct {
	char	*buf; // buffer
	int	size; // buffer size in bytes
	int 	len;  // data length in bytes
	int	off;  // current offset
}fmemopen_cookie_t;

int readfn(void *cookie, char *buf, int nbytes);
int writefn(void *cookie, const char *buf, int nbytes);
fpos_t seekfn(void *cookie, fpos_t offset, int whence);
int closefn(void *cookie);

/*
 * Function: fmemopen
 * ------------------
 * 	A stream open function, return a FILE pointer
 *
 * @param buf 	A buffer for file operations
 * @param size 	Buffer size
 * @param mode	File open mode
 * @return	A FILE pointer on success, otherwise a NULL pointer
 */
FILE *fmemopen(void *restrict buf, size_t size, const char *mode){
	// If buf is NULL, we should allocate a memory with size bytes of memory
	if(buf == NULL) buf = malloc(size * sizeof(char));

	// Initialize a cookie for stream
	fmemopen_cookie_t *c = malloc(sizeof(fmemopen_cookie_t));
	c->buf = buf;
	c->size = size;
	c->len = 0;
	c->off = 0;

	// Handle modes
	// I think we don't need to implement x, b in this assignment
	if(mode == NULL) return NULL;
	int read_flag = 0;
	int write_flag = 0;
	switch(mode[0]){
		case 'r':
			read_flag = 1;
			c->len = c->size;
			break;
		case 'w':
			write_flag = 1;
			break;
		case 'a':
			write_flag = 1;
			c->len = strnlen(c->buf, c->size);
			c->off = strnlen(c->buf, c->size);
			break;
		default:
			return NULL;
	}
	if(strlen(mode) >= 2 && mode[1] == '+'){
		read_flag = write_flag = 1;
	}
	
	return	funopen(c,
			((read_flag == 1) ? readfn : NULL),
			((write_flag == 1) ? writefn : NULL),
			seekfn,
			closefn);
}

/*
 * Function: readfn
 * ----------------
 *  	Read file stream to specific buffer
 *
 * @param cookie	Metadata of file stream
 * @param buf		Buffer
 * @param nbytes	Number of bytes to read
 * @return		Number of bytes been read
 */
int readfn(void *cookie, char *buf, int nbytes){
	fmemopen_cookie_t *c = (fmemopen_cookie_t*)(cookie);
	nbytes = MIN(nbytes, c->len - c->off);
	if(nbytes <= 0) return 0;
	strncpy(buf, c->buf, nbytes);
	c->off += nbytes;
	return nbytes;
}

/*
 * Function: writefn
 * -----------------
 *	Write to file stream
 *
 * @param cookie	Metadata of file stream
 * @param buf		Buffer
 * @param nbytes	Number of bytes to write
 * @return		Number of bytes been wriiten
 */
int writefn(void *cookie, const char *buf, int nbytes){
	fmemopen_cookie_t *c = (fmemopen_cookie_t*)(cookie);
	nbytes = MIN(nbytes, c->size - c->off - 1); // -1 for ending '\0'
	if(nbytes <= 0) return 0;
	strncpy(c->buf, buf, nbytes);
	c->off += nbytes;
	c->len  = MAX(c->off, c->size - 1);
	c->buf[c->off] = '\0';
	return nbytes;
}

/*
 * Function: seekfn
 * ----------------
 *  	Seek to specific offset with condition whence of file stream
 *
 * @param cookie	Metadata of file stream
 * @param offset	Number of byte offsets
 * @param whence	Define the entry point and offset count
 * @return		Resulting seek position in bytes
 */
fpos_t seekfn(void *cookie, fpos_t offset, int whence){
	fmemopen_cookie_t *c = (fmemopen_cookie_t*)(cookie);
	switch(whence){
		case SEEK_SET:
			if(offset >= c->size || offset < 0) return -1;
			c->off = offset;
			break;
		case SEEK_CUR:
			if(c->off + offset >= c->size || c->off + offset < 0) return -1;
			c->off += offset;
			break;
		case SEEK_END:
			if(c->size + offset < 0 || c->size + offset >= c->size) return -1;
			c->off = c->size + offset;
			break;
		case SEEK_HOLE:
			if(offset >= c->size || offset < 0) return -1;
			while(c->buf[offset] != 0 && offset < c->size) offset++;
			if(offset >= c->size) return -1;
			c->off = offset;
			break;
		case SEEK_DATA:
			if(offset >= c->size || offset < 0) return -1;
			while(c->buf[offset] == 0 && offset < c->size) offset++;
			if(offset >= c->size) return -1;
			c->off = offset;
			break;
		default:
			return -1;
	}
	return c->off;
}

/*
 * Function: closefn
 * -----------------
 *	Close a file stream
 *
 * @param cookie	Metadata of file stream
 * @return 		0 if success, otherwise -1
 */
int closefn(void *cookie){
	fmemopen_cookie_t* c = (fmemopen_cookie_t*)(cookie);
	free(c); // we are not able to check whether free is success or not
	return 0;
}


int main(){
	// Task1: Write "hello, world" in the file stream
	char *buf = malloc(100);
	FILE *fp = fmemopen(buf, 100, "w+");
	fprintf(fp, "hello, world");

	// Task2: Seek the position of "world" in the file stream
	fseek(fp, 7, SEEK_SET);

	// Task3: Read the word "world" from the file stream and print it. Then, print the whole sentence "hello, world".
	char *buf2 = malloc(100);
	fread(buf2, sizeof(char), 5, fp);
	printf("%s\n", buf2);
	fseek(fp, 0, SEEK_SET);
	char *buf3 = malloc(100);
	fread(buf3, sizeof(char), sizeof("hello, world"), fp);
	printf("%s\n", buf3);
	
	// Task4: Close the file stream correctly
	fclose(fp);

	// Don't forget to free the buffer
	free(buf);
	return 0;
}
