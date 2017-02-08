#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>



void ReadArgs(char *in, char **argv, int size);
void PrintArgs(char **argv);


int main(){
	char s[200];
	char **argv;
	argv = malloc(sizeof(char*));
	// Read a string from the stdin
	printf("Enter a string: ");
	fgets(s, sizeof s, stdin);
	// Extract arguments and print them
	ReadArgs(s, argv, 10);
	PrintArgs(argv);
	free(argv);
	*argv = NULL;
	argv = NULL;
	


}



void ReadArgs(char *in, char **argv, int size){

	char *sep = " ";
	char *word;
	int counter = 0;
	in[strlen(in)-1] = '\0';
	for(word = strtok(in, sep); word; word = strtok(NULL, sep)){
		// if within range
		if (counter == 0){
			*(argv + counter) = calloc(size, sizeof(char));
		}
		// if exceeds
		if(counter >= size){
			*(argv + counter)  = malloc(sizeof(char));
		}
		*(argv + counter) = strdup(word);
		counter ++;
	}
	if (counter < size){
		*(argv + counter)  = NULL;

	}else{
		*(argv + counter) = malloc(sizeof(char));
		*(argv + counter) = NULL;
	}
	
}

void PrintArgs(char **argv){
	int i = 0;
	for (i = 0; argv[i] != NULL; i ++){
		printf("argv[%d] = '%s'\n", i, argv[i]);
		free(argv[i]);
	}
	free(argv[i]);

}
	