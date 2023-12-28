#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

void
sleep_us(unsigned int nusecs)
{
    struct timeval tval;
    tval.tv_sec = nusecs / 1000000;
    tval.tv_usec = nusecs % 1000000;
    select(0, NULL, NULL, NULL, &tval);
}

int main(int argc, char *argv[])
{
    unsigned int t = atoi(argv[1]);

    struct timeval start, end;
    gettimeofday(&start, NULL);
    sleep_us(t);
    gettimeofday(&end, NULL);

    long tt = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    printf("Sleep time: %ld us\n", tt);

    return 0;
}