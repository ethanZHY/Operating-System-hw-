// composed by Yu Zhang 001259692
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv){

	char* action = argv[1];

	if (strcmp(action, "info") == 0){
		// printf("info\n");
		if (argc < 3){
			printf("info: <file> not found\n");
			return -1;
		}
		struct stat buf;
		char* path = argv[2];
		if(stat(path, &buf) != 0){
			perror("Error:");
			exit(-1);
		}
		printf("Inode: %llu\n", buf.st_ino);
		printf("Size: %llu\n", buf.st_size);
		printf("Permission: %o\n", buf.st_mode); 


	}else if (strcmp(action, "link") == 0){
		// printf("link\n");
		if (argc<4){
			printf("link: fault args format\n");
			return -1;
		}
		if (link(argv[2], argv[3]) == -1){
			perror("Error");
			exit(-1);
		}

	}else if (strcmp(action, "symlink") == 0){
		
		if (argc<4){
			printf("link: fault args format\n");
			return -1;
		}
		if (symlink(argv[2], argv[3]) == -1){
			perror("Error");
			exit(-1);
		}
	}else if (strcmp(action, "rm") == 0){

		if (argc<3){
			printf("rm: fault args format\n");
			return -1;
		}
		else{
			char *arg[3] = {"rm", argv[2], NULL};
			if (execvp(arg[0], arg) == -1){
				perror("Error");
				exit(1);
			}
		}

	}else{
		printf("none\n");
	}


}