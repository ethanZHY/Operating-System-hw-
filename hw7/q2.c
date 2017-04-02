#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "barrier.h"

#define THREADS 5

struct barrier_t barrier;

void *myThread(void *arg){
	pthread_t id = pthread_self();
	printf("Execution starts, thread ID: %d\n", (int)id);
	barrier_wait(&barrier, (int)arg);
	printf("Execution ends, thread ID: %d\n", (int)id);
	return NULL;
}


int main()
{	
	printf("parent starts\n");
	barrier_init(&barrier, THREADS);
	pthread_t p[THREADS];
	for (int i = 0; i < THREADS; i++){
		pthread_create(&p[i], NULL, myThread, i);
	}
	for (int i = 0; i < THREADS; i++){
		pthread_join(p[i],NULL);
	}
	printf("parent finishes\n");
	return 0;
}