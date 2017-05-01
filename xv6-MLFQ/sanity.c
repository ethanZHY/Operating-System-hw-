#include "types.h"
#include "user.h"

int main(int argc, char ** argv){
	int child[10];
	int i = 0;
	while(i < 5) {
		child[i] = fork();
		if (child[i] < 0){
			printf(1,"Error: fork\n");
			exit();
		}
		else if (child[i] == 0){  // children
			// doWork
			int k = 0;
			while(k < 100){
				k++;
				printf(1, "pid: %d prio: %d ticks: %d\n",(int)getpid(), (int)getprio(), (int)getticks());
			}
			exit();
		}
		else{					// parent
			i++;
		}
	}
	int pid;
	while((pid = wait()) > 0){
		continue;
	}
	exit();
}



