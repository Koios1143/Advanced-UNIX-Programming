#include <stdio.h>
#include <time.h>

int main()
{
    time_t t;
    struct tm *p;
    t = time(NULL);
    p = localtime(&t);

    //“Hour:Min:Sec, Week day
    // Month Date, Year” (24-hour format, full month name). For example, 10:35:03, Tuesday November
    // 29, 2016.
    char *week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    char *month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September",
                     "October", "November", "December"};
    printf("%02d:%02d:%02d, %s %s %d, %d\n", 
           p->tm_hour, 
           p->tm_min, 
           p->tm_sec, 
           week[p->tm_wday], 
           month[p->tm_mon], 
           p->tm_mday, 
           p->tm_year + 1900);
    return 0;
}