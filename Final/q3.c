#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void alarm_handler(int signo)
{
    printf("Alarm!\n");
}

void setAlarm(int sec)
{
    signal(SIGALRM, alarm_handler);
    alarm(sec);
}

void clearAlarm()
{
    alarm(0);
}

int main()
{
    setAlarm(2); //set 2 sec alarm at 0s, will finish at 2s after execution
    sleep(1);
    setAlarm(6); //set 6 sec alarm at 1s, will finish at 7s after execution
    sleep(1);
    setAlarm(3); //set 3 sec alarm at 2s, will finish at 5s after execution
    sleep(4);
    clearAlarm();

    return 0;
}
