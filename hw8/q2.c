# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>
# define MAX 4
# define THNUM 2

pthread_t p[THNUM];
pthread_mutex_t grid[MAX][MAX];

// move packet
void* move_packet(void* ptr){
	int id = (int) ptr;
	while (1){
		int sx = -1, sy = -1, dx = -1, dy = -1;
		srand(time(NULL));
		while (sx == dx && sy == dy){
			sx = rand()%(MAX);
			sy = rand()%(MAX);
			dx = rand()%(MAX);
			dy = rand()%(MAX);	
		}
		pthread_mutex_lock(&grid[sx][sy]);
		printf("packet %d: starts at %d/%d, destination is %d/%d\n", id, sx, sy, dx, dy);
		// move at X axis
		while (sx != dx){
			if (sx > dx){
				printf("packet %d: now at %d/%d, next stop is %d/%d\n", id, sx, sy, sx-1, sy);
				pthread_mutex_lock(&grid[sx-1][sy]);
				pthread_mutex_unlock(&grid[sx][sy]);
				sx--;
			}
			if (sx < dx){
				printf("packet %d: now at %d/%d, next stop is %d/%d\n", id, sx, sy, sx+1, sy);
				pthread_mutex_lock(&grid[sx+1][sy]);
				pthread_mutex_unlock(&grid[sx][sy]);
				sx++;
			}
			
		}
		// move at Y axis
		while (sy != dy){
			if (sy > dy){
				printf("packet %d: now at %d/%d, next stop is %d/%d\n", id, sx, sy, sx, sy-1);
				pthread_mutex_lock(&grid[sx][sy-1]);
				pthread_mutex_unlock(&grid[sx][sy]);
				sy--;
			}
			if (sy < dy){
				printf("packet %d: now at %d/%d, next stop is %d/%d\n", id, sx, sy, sx, sy+1);
				pthread_mutex_lock(&grid[sx][sy+1]);
				pthread_mutex_unlock(&grid[sx][sy]);
				sy++;
			}

		}
		printf("packet %d: reaches destination %d/%d\n\n", id, sx, sy);
		pthread_mutex_unlock(&grid[sx][sy]);
	}
	return NULL;
}


int main(){
	// init mutex
	for (int i = 0; i<MAX; i++){
		for (int j = 0; j<MAX; j++){
			pthread_mutex_init(&grid[i][j], NULL);
		}
	}
	// create children threads
	for (int k = 0; k < THNUM; k++){
		pthread_create(&p[k], NULL, move_packet, k);
	}
	// Wait for children
	for (int k = 0; k < THNUM; k++){
		pthread_join(p[k], NULL);
	}
	// Done
	return 0;
}