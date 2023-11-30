#include<stdio.h>
#include<pthread.h>

typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int count;
	int max_count;
} pthread_barrier_t_;

int pthread_barrier_init_(pthread_barrier_t_ *restrict barrier,
			const pthread_barrierattr_t *attr,
			unsigned count){
	barrier->count = 0;
	barrier->max_count = count;
	pthread_mutex_init(&barrier->mutex, NULL);
	pthread_cond_init(&barrier->cond, NULL);
	return 0;
}

int pthread_barrier_wait_(pthread_barrier_t_ *barrier){
	pthread_mutex_lock(&barrier->mutex);
	barrier->count++;
	if(barrier->count >= barrier->max_count){
		barrier->count = 0;
		pthread_cond_broadcast(&barrier->cond);
		pthread_mutex_unlock(&barrier->mutex);
		return PTHREAD_BARRIER_SERIAL_THREAD;
	}
	else{
		pthread_cond_wait(&barrier->cond, &barrier->mutex);
		pthread_mutex_unlock(&barrier->mutex);
		return 0;
	}
}

int pthread_barrier_destroy_(pthread_barrier_t_ *barrier){
	pthread_mutex_destroy(&barrier->mutex);
	pthread_cond_destroy(&barrier->cond);
	return 0;
}

static pthread_barrier_t_ barrier;

void *worker(void *arg){
	// arg is just dummy argument
	//printf("Thread %lld waiting\n", pthread_self());
	pthread_barrier_wait_(&barrier);
	printf("Thread %lld running\n", pthread_self());
	return NULL;
}

int main(){
	pthread_t tid[5];
	pthread_barrier_init_(&barrier, NULL, 6);
	for(int i=0 ; i<5 ; i++){
		printf("Starting thread %d\n", i);
		pthread_create(&tid[i], NULL, worker, NULL);
	}
	pthread_barrier_wait_(&barrier);
	for(int i=0 ; i<5 ; i++){
		pthread_join(tid[i], NULL);
	}
	//pthread_barrier_destroy_(&barrier);
	return 0;
}
