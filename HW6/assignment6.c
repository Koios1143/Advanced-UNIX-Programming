//#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PSCMD "ps -o pid,ppid,state,tty,command"

int main(){
    pid_t pid;

    if((pid = fork()) < 0){
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
        exit(0);
    
    /* parent */
    sleep(4);
    system(PSCMD);

    exit(0);
}