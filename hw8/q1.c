#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t forks[5];

int left(int p)
{
	return p;
}
int right(int p)
{
	return (p + 1) % 5;
}
// obviously we need to modify the way p4 get its fork;
void getForks(int p)
{
	printf("%d tries to get forks\n", p);
	if (right(p) == 0){
		sem_wait(&forks[right(p)]);
		sem_wait(&forks[left(p)]);
	}
	else{
		sem_wait(&forks[left(p)]);
		sem_wait(&forks[right(p)]);
	}
	printf("%d gets the forks\n", p);
}
void putForks(int p)
{
	printf("%d puts the forks\n", p);
	sem_post(&forks[left(p)]);
	sem_post(&forks[right(p)]);
}

void *philosopher(void *arg)
{
	int i;
	long p = (long) arg;
	while (1)
	{
	// Think
	for (i = 0; i < 100000; i++);
	// Get forks
	getForks(p);
	// Eat
	for (i = 0; i < 100000; i++);
	// Put forks
	putForks(p);
	}
}
int main()
{
// Initialize semaphores
	long i;
	for (i = 0; i < 5; i++)
		sem_init(&forks[i], 0, 1);
	// Create child threads
	pthread_t p[5];
	for (i = 0; i < 5; i++)
		pthread_create(&p[i], NULL, philosopher, (void *) i);
	// Wait for children
	for (i = 0; i < 5; i++)
		pthread_join(p[i], NULL);
	// Done
	return 0;
}