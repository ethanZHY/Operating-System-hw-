#include <stdlib.h>
#include <string.h>
#include <stdio.h>



int get_args(char *in, char **argv, int max_args){

	char *sep = " ";
	char *word;
	int n = 0;
	in[strlen(in)-1] = '\0';
	for(word = strtok(in, sep); word; word = strtok(NULL, sep))
			
		if (n <= max_args){
			argv[n] = strdup(word);	
			n++;		
		}
	return n;
}

void print_args(int argc, char **argv){
	for(int i = 0; i < argc; i++){
		printf("argv[%d] = '%s'\n", i, argv[i]);
	}

}

int main()
{
	char s[200];
	char *argv[10];
	int argc;
	// Read a string from the user
	printf("Enter a string: ");
	fgets(s, sizeof s, stdin);
	// Extract arguments and print them
	argc = get_args(s, argv, 10);
	print_args(argc, argv);
}