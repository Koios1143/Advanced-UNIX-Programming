#include<time.h>
#include<stdio.h>
#include<sys/time.h>

int main(){
	// Get unix timestampe (Epoch) by time()
	time_t tloc;
	time(&tloc);
	// Transfer time_t to tm by localtime()
	char buf[100];
	struct tm *timeptr = localtime(&tloc);
	// Print format string by strftime()
	strftime(buf, 100, "%a %b %d %H:%M:%S %Z %G\n", timeptr);
	printf(buf);
	return 0;
}
