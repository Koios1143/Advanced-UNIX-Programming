#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>
#define PSCMD "ps -o pid,pgid,tpgid -p "
extern int errno;

int main(){
	pid_t pid;
	char cmd[100];
	if((pid = fork()) < 0){
		// some error occured
		perror("Error occured while running fork: ");
		return errno;
	}
	else if(pid > 0){
		// parent
		//printf("\nOridinal Status: \n");
		//sprintf(cmd, "%s %d\0", PSCMD, getpid());
		system(cmd);
	}
	else{
		// child
		sleep(1);
		pid = setsid();
		//printf("\nNew Status: \n");
		sprintf(cmd, "%s %d\0", PSCMD, getpid());
		system(cmd);
		exit(0);
	}
	wait(NULL);
	return 0;
}
