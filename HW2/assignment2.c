#include"sys/types.h"
#include"sys/stat.h"
#include"unistd.h"
#include"fcntl.h"
#include"stdio.h"
int main(int argc, char *argv[]){

    // check arguments
    // arguments should include "filename", "source_file" and "dest_file"
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
    
    // check source_file exists
    int source_fd = open(source_file, O_RDONLY);
    if(source_fd == -1){
        fprintf(stderr, "cp: cannot stat '%s': No such file or directory\n", source_file);
        close(source_fd);
        return 2;
    }

    // open dest_file
    int dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(dest_fd == -1){
        fprintf(stderr, "Some error occurred.");
        return 3;
    }

    // read source and write destination
    char buffer[4096];
    int read_sz;
    // read start from begining
    lseek(source_fd, 0, SEEK_SET);
    while((read_sz = read(source_fd, buffer, sizeof(buffer))) > 0){
        // move to the end of the dest file
        lseek(dest_fd, 0, SEEK_END);
        // write the content
        write(dest_fd, buffer, read_sz);
        // move to next step
        lseek(source_fd, read_sz, SEEK_CUR);
    }
    close(source_fd);
    close(dest_fd);
    return 0;
}