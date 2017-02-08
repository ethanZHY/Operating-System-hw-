/**This code force the OS to perform a context switch
* after each message is printed,by synchronizing 
* the parent and child processes with two pipes
**/


#import <stdlib.h>
#import <stdio.h>
#import <unistd.h>


int main(){
	// Parent to child
	int fds_PC[2];
	// Child to parent
	int fds_CP[2];

	if(pipe(fds_PC) == -1){
		printf("Error in fds_PC\n");
	}
	if(pipe(fds_CP) == -1){
		printf("Error in fds_CP\n");
	}

	int ret = fork();

	// error
	if (ret < 0){
		perror("fork");
		return 1;

	}

	// child
	if(ret == 0){
		close(fds_PC[1]);
		close(fds_CP[0]);
		int c = 1;
	
		//c to p
		for(int i = 0; i < 5; i++){

			read(fds_PC[0], &c, sizeof(c));
			// # commented lines are used for debug only
			//printf("child %d\n", c);
			//fflush(stdout);
			//c = c*2;
			printf("%d, Child\n", i + 1);
			fflush(stdout);
			write(fds_CP[1], &c, sizeof(c));

		}

		return 0;
	}

	//parent
	else if (ret > 0){
		close(fds_CP[1]);
		close(fds_PC[0]);
		int c = 1;

		// p to c
		for (int i = 0; i < 5; i++){
			write(fds_PC[1], &c, sizeof(c));
			printf("%d, Parent\n", i + 1);
			fflush(stdout);
			read(fds_CP[0], &c, sizeof(c));
			// # commented lines are used for debug only
			//printf("parent %d\n", c);	
			//fflush(stdout);	
			//c *= 2;
		}
		wait(NULL);
		return 0;
	}
	return -1;
}