#include"fcntl.h"
#include"stdio.h"
#include"errno.h"
#include"ctype.h"
#include"stdlib.h"
#include"unistd.h"
#include"getopt.h"
#include"string.h"

// declare arguemnt flags, 0 by default
int c_flag, u_flag, i_flag;

// declare longopts for getopt_long function
static const struct option long_opts[] = 
{
	{"count",	no_argument,	NULL, 'c'},	
	{"unique",	no_argument,	NULL, 'u'},
	{"ignore-case",	no_argument,	NULL, 'i'},
	{NULL,		NULL,		NULL,  0}
};

// A simple function that change a string into lowercase
char* str_lower(char* str){
	if(str == NULL) return NULL;
	char* ret = malloc(sizeof(str));
	strcpy(ret, str);
	for(char *p=ret ; *p ; p++){
		*p = tolower(*p);
	}
	return ret;
}

char* mstrncpy(char* str, int length){
	char* ret = malloc((length + 1) * sizeof(char));
	strncpy(ret, str, length);
	ret[length] = '\0';
	return ret;
}

int main(int argc, char* argv[]){
	// declare input_file_pointer and output_file_pointer
	FILE *ifp = stdin, *ofp = stdout;

	// process arguments by getopt_long
	int val;
	while((val = getopt_long(argc, argv, "+cui", long_opts, NULL)) != -1){
		switch(val) {
			case 'c':
				c_flag = 1;
				break;
			case 'u':
				u_flag = 1;
				break;
			case 'i':
				i_flag = 1;
				break;
			case '?':
			default:
				fprintf(stderr, "usage: ./mocktest [-c | -u] [-i] [input [output]]\n");
				return 1;
		}
	}
	
	// ignore those arguments, so that we can check file arguments
	// optind is extern by getopt.h
	argc -= optind;
	argv += optind;

	// check input file
	if(argc > 0){
		ifp = fopen(argv[0], "r");
		if(ifp == NULL){
			perror("Input file error: ");
			return errno;
		}
	}
	// check output file
	if(argc > 1){
		ofp = fopen(argv[1], "w");
		if(ofp == NULL){
			perror("Output file error: ");
			return errno;
		}
	}

	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	int count = 1;
	char *prev = NULL;
	while((linelen = getline(&line, &linecap, ifp)) > 0){
		if(line[linelen - 1] == '\n')
			line[--linelen] = '\0';
		if(prev == NULL){
			prev = mstrncpy(line, linelen);
			count = 1;
			continue;
		}
		// ignore flag is on, and current string different from previous or
		// ignore flag is off, and current string different from previos
		if((i_flag == 1 && (strcmp(str_lower(prev), str_lower(line))) != 0) ||
		   (i_flag == 0 && (strcmp(prev, line) != 0))){
			// if we should output the current result
			if(!(u_flag && count > 1)){
				if(c_flag == 1){
					fprintf(ofp, "%4d %s\n", count, prev);
				}
				else{
					fprintf(ofp, "%s\n", prev);
				}
			}
			// reset counter, update prev
			count = 1;
			free(prev);
			prev = mstrncpy(line, linelen);
		}
		else{
			// In any situation, prev is equal to line, then just update count
			count++;
		}
	}
	// output the last result
	//output_current(ofp, &count, &prev);
	if(!(u_flag && count > 1)){
		if(c_flag == 1){
			fprintf(ofp, "%4d %s\n", count, prev);
		}
		else{
			fprintf(ofp, "%s\n", prev);
		}
	}
	return 0;
}
