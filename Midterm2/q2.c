#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if(argc != 2)
        printf("argc error");

    if((dp = opendir(argv[1])) == NULL)
        printf("can't open %s", argv[1]);
    
    struct stat buf;
    char actual_path[513];
    char symbolic_path[513];
    ssize_t len;

    while((dirp = readdir(dp)) != NULL)
    {
        if(dirp->d_type == DT_LNK)
        {
            strcpy(symbolic_path, argv[1]);
            strcat(symbolic_path, "/");
            strcat(symbolic_path, dirp->d_name);
            //printf("%s\n", symbolic_path);
            len = readlink(symbolic_path, actual_path, sizeof(actual_path));
            if(len == -1)
                printf("readlink error");
            else{
                actual_path[len] = '\0';
                printf("%s -> %s\n", dirp->d_name, actual_path);
            }
        }   
    }

    closedir(dp);
    return 0;
}
