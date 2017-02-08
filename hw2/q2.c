#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void ppwrite(int fd[]);
void ppread(int fd[]);

int main(int argc, char **argv){


	int pid;
	int fds[2];
	int err = pipe(fds);
	if (err == -1){
		perror("pipe");
		return 1;
	}
	ppwrite(fds);
	ppread(fds);
	close(fds[0]);
	close(fds[1]);
	

	while ((pid = wait(NULL)) > 0)	
		fprintf(stderr, "Process %d finished\n", pid);
	exit(0);
}

void ppwrite(int fd[]){
	
	switch(fork()){
		case 0: 
			close(fd[0]);
			close(1);
			dup(fd[1]);
			char *argv[3];
			argv[0] = "ls";
			argv[1] = "-l";
			argv[2] = NULL ;
			execvp(argv[0], argv);
		case -1:
			perror("fork");
			exit(1);
		default:
			break;
	}
}

void ppread(int fd[]){
	
	switch(fork()){
		case 0: 
			close(fd[1]);
			close(0);
			dup(fd[0]);
			char *argv[2];
			argv[0] = "wc";
			argv[1] = NULL ;
			execvp(argv[0], argv);
		case -1:
			perror("fork");
			exit(1);
		default:
			break;
	}
}

