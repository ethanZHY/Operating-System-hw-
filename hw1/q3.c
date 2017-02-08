#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	

	//fork
	int child = fork();
	if (child < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (child == 0){
		int num;
		printf("Enter a number: ");
		scanf( "%d",&num);
		exit(num);


	}
	else{
		int status;
		wait(&status);
		//printf("%d, %d \n", WIFEXITED(status), WIFSIGNALED(status));
		printf("Child exited with status %d\n", WEXITSTATUS(status));

	


	}

	return 0;
	
}