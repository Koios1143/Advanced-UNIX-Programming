#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAXSTRINGSZ 4096

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char** environ;

static void thread_init(void)
{
	pthread_key_create(&key, free);
}

// for output debug message
char test[512][512];
int cnt = 0;

// for preventing initialize process dead
static int init_flag = 1;

char* getenv(const char *name)
{
	// store debug message
	sprintf(test[cnt++], "%s", name);

	int     i, len;
	char    *envbuf;
	// buffer for initialize process
	static char	buf[MAXSTRINGSZ];
	
	if(init_flag == 0){
		pthread_once(&init_done, thread_init);
		pthread_mutex_lock(&env_mutex);
		envbuf = (char *)pthread_getspecific(key);
	
		if (envbuf == NULL) {
			envbuf = malloc(MAXSTRINGSZ);
			if (envbuf == NULL) {
				pthread_mutex_unlock(&env_mutex);
				return(NULL);
			}
			pthread_setspecific(key, envbuf);
		}
	}
	else{
		envbuf = buf;
	}

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++) {
		if ((strncmp(name, environ[i], len) == 0) &&
				(environ[i][len] == '=')) {
			strncpy(envbuf, &environ[i][len + 1], MAXSTRINGSZ -1);
			if(init_flag == 0){
				pthread_mutex_unlock(&env_mutex);
			}
			return(envbuf);
		}
	}

	if(init_flag == 0){
		pthread_mutex_unlock(&env_mutex);
	}

	return(NULL);
}
int main(int argc, char* argv[])
{
	// print out debug messages
	for(int i=0 ; i<cnt ; i++){
		printf("%s\n", test[i]);
	}
	// set init flag
	init_flag = 0;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <envvar>\n", argv[0]);
		return 1;
	}

	char* val = getenv(argv[1]);
	printf("%s = %s\n", argv[1], val);

	return 0;
}
