#include<stdio.h>
#include<pthread.h>

// we define our own pthread_barrier_t
// we only care about count and max_count
// in order to differentiate this from real one, we add a single _ at the end
typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int count;
	int max_count;
} pthread_barrier_t_;

// initiate barrier, include mutex, condition, count and max_count
// we ignore attr and some error handling here
int pthread_barrier_init_(pthread_barrier_t_ *restrict barrier,
			const pthread_barrierattr_t *attr,
			unsigned count){
	barrier->count = 0;
	barrier->max_count = count;
	pthread_mutex_init(&barrier->mutex, NULL);
	pthread_cond_init(&barrier->cond, NULL);
	return 0;
}

// wait until the count reach max_count
int pthread_barrier_wait_(pthread_barrier_t_ *barrier){
	pthread_mutex_lock(&barrier->mutex);
	barrier->count++;
	if(barrier->count >= barrier->max_count){
		barrier->count = 0;
		// using cond broadcast to notify other threads to move on
		pthread_cond_broadcast(&barrier->cond);
		pthread_mutex_unlock(&barrier->mutex);
		// according to the man page, one should return PTHREAD_BARRIER_SERIAL_THREAD
		return PTHREAD_BARRIER_SERIAL_THREAD;
	}
	else{
		pthread_cond_wait(&barrier->cond, &barrier->mutex);
		pthread_mutex_unlock(&barrier->mutex);
		// while others will return 0
		return 0;
	}
}

// basically just call destroy function provided by mutex and cond
int pthread_barrier_destroy_(pthread_barrier_t_ *barrier){
	pthread_mutex_destroy(&barrier->mutex);
	pthread_cond_destroy(&barrier->cond);
	return 0;
}

static pthread_barrier_t_ barrier;

// a worker function, wait until barrier count to 6, which means all thread are set
// then output the text message
void *worker(void *arg){
	// arg is just dummy argument
	pthread_barrier_wait_(&barrier);
	printf("Thread %lld running\n", pthread_self());
	return NULL;
}

int main(){
	// first create 5 threads and initiate barrier
	pthread_t tid[5];
	pthread_barrier_init_(&barrier, NULL, 6);
	// then before create the thread, output the text as spec needs
	for(int i=0 ; i<5 ; i++){
		printf("Starting thread %d\n", i);
		pthread_create(&tid[i], NULL, worker, NULL);
	}
	// this wait is for notify that all threads are already been created
	pthread_barrier_wait_(&barrier);
	// we should end main process until all threads are done with their jobs
	for(int i=0 ; i<5 ; i++){
		pthread_join(tid[i], NULL);
	}
	// then we can destroy everything!
	pthread_barrier_destroy_(&barrier);
	return 0;
}
