#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
    time_t rawtime;
    struct tm * timeinfo;

    while(1){
        time (&rawtime);
        timeinfo = localtime (&rawtime);

        printf("%d\n", timeinfo->tm_sec);

        for(int i=0; i<6; i++){ 
            sleep(10);
        }
    }
}