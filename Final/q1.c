#include <pthread.h>
#include <stdio.h>
#include <signal.h>

void thread1_handler(int signo)
{
    printf("T1 handing SIGINT\n");
}

void* thread1(void* arg)
{
    signal(SIGINT, thread1_handler);
    return NULL;
}

void thread2_handler(int signo)
{
    printf("T2 handing SIGTERM\n");
}

void* thread2(void* arg)
{
    signal(SIGTERM, thread2_handler);
    return NULL;
}

void thread3_handler(int signo)
{
    printf("T3 handing SIGUSR1\n");
}

void* thread3(void* arg)
{
    signal(SIGUSR1, thread3_handler);
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    while(1);

    return 0;
}