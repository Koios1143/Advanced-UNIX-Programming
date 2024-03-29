#include"sys/types.h"
#include"sys/stat.h"
#include"unistd.h"
#include"fcntl.h"
#include"stdio.h"
#include"errno.h"

extern int errno;

int main(int argc, char *argv[]){
    // check arguments
    // which should include "filename", "source_file" and "dest_file"
    if(argc == 1){
        fprintf(stderr, "cp: missing file operand\n");
        return 1;
    }
    else if(argc == 2){
        fprintf(stderr, "cp: missing file operand after '%s'\n", argv[1]);
        return 1;
    }
    
    char *source_file = argv[1];
    char *dest_file = argv[2];
    
    // open source_file and check if source_file exists
    int source_fd = open(source_file, O_RDONLY);
    if(source_fd == -1){
        fprintf(stderr, "cp: cannot stat '%s': No such file or directory\n", source_file);
        close(source_fd);
        return 2;
    }

    // open dest_file and check if there's an error
    int dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(dest_fd == -1){
        perror("Error occurred: ");
        return errno;
    }

    // read source and write destination
    char buffer[4096];
    int read_sz;

    // read and write from the beginning of the files
    lseek(source_fd, 0, SEEK_SET);
    lseek(dest_fd, 0, SEEK_SET);

    while((read_sz = read(source_fd, buffer, sizeof(buffer))) > 0){
        // write the content
        if (write(dest_fd, buffer, read_sz) == -1)
            fprintf(stderr, "write error");
    }

    // close the files
    close(source_fd);
    close(dest_fd);

    return 0;
}