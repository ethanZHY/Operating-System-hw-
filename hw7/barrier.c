#include <stdio.h>
#include "barrier.h"

void barrier_init(struct barrier_t *barrier, int count)
{
	barrier->count = count;
	if (count > BARRIER_MAX_THREADS){
		printf("fault");
		return;
	}
	for (int i = 0; i < count; i++)
		barrier->reached[i] = 0;
	pthread_mutex_init(&barrier->mutex, NULL);
	for (int i = 0; i < count; i++)
		pthread_cond_init(&barrier->cond[i], NULL);
}



void barrier_wait(struct barrier_t *barrier, int id)
{
	// mark current thread as having reached the barrier
	barrier->reached[id] = 1;
	pthread_mutex_lock(&barrier->mutex);
	// check if everyone arrived in the barrier
	int n = 0;
	for (int i = 0; i < barrier->count; i++){
		n = n + barrier->reached[i];
	}
	// suspend current thread in its associated cond	
	if (n < barrier->count){
		pthread_cond_wait(&barrier->cond[id], &barrier->mutex);
	}else{
		// wake everyone up and continue
		int i;
		for (i = 0; i < barrier->count; i++)
			pthread_cond_signal(&barrier->cond[i]);
	}
	pthread_mutex_unlock(&barrier->mutex);
}