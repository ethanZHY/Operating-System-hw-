#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_SUB_COMMANDS 5
#define MAX_ARGS 10


	struct SubCommand{
		char *line;
		char *argv[MAX_ARGS];
	};

	struct Command{
		struct SubCommand sub_commands[MAX_SUB_COMMANDS];
		int num_sub_commands;
		char *stdin_redirect;
		char *stdout_redirect;
		int background;
	};


void ReadRedirectsAndBackground(struct Command *command);
void PrintCommand(struct Command *command);
void ReadArgs(char *in, char **argv, int size);
void PrintArgs(char **argv);
void ReadCommand(char *line, struct Command *command);
void test();

int main(){

	struct Command *command = malloc(sizeof(struct Command));
	char line[200];
	printf("Please enter an input string\n");
	fgets(line, sizeof(line), stdin);
	line[strlen(line)-1] = '\0';

	ReadCommand(line, command);
	ReadRedirectsAndBackground(command);

	// read args for every sub-command
	for (int i = 0; i < command -> num_sub_commands; i++){
		ReadArgs(command->sub_commands[i].line, command->sub_commands[i].argv, MAX_ARGS);
	}

	PrintCommand(command);
	free(command);

	return 0;
}

void ReadRedirectsAndBackground(struct Command *command){

	//initialization
	command -> stdin_redirect = NULL;
	command -> stdout_redirect = NULL;
	command -> background = 0;

	int num_sub = command -> num_sub_commands;

	// travers all sub-command
	for (int i = 0; i < num_sub; i++){

		int limbo = strlen(command -> sub_commands[i].line);
		int k = 0;

		//check the end of each line
		// if any line contains '&', do not check anymore
		if (command -> sub_commands[i].line[limbo - 1] == '&' && k != 1){
			command -> background = 1;
			command -> sub_commands[i].line[limbo - 1] = '\0';
			k++;
		}
		// process the 1st subc
		if (i == 0){
			for (int j = 0; j < limbo - 1; j++){
				if (command -> sub_commands[i].line[j] == '<'){
					command -> stdin_redirect = command -> sub_commands[i].line + j + 1;
					command -> sub_commands[i].line[j] = '\0';
				}
				if (command -> sub_commands[i].line[j] == '>'){
					command -> stdout_redirect = command -> sub_commands[i].line + j + 1;
					command -> sub_commands[i].line[j] = '\0';
				}	
			}
		}
		// process the last subc
		else if (i == num_sub - 1){
			for (int j = 0; j < limbo - 1; j++){
				if (command -> sub_commands[i].line[j] == '>'){
					command -> stdout_redirect = command -> sub_commands[i].line + j + 1;
					command -> sub_commands[i].line[j] = '\0';
				}
				if (command -> sub_commands[i].line[j] == '<'){
					command -> stdin_redirect = command -> sub_commands[i].line + j + 1;
					command -> sub_commands[i].line[j] = '\0';

				}
			}

		}
		else continue;

	}

}


void ReadCommand(char *line, struct Command *command){

	char *sep = "|";
	char *word;
	int i = 0;

	// split command into sub-commands
	for (word = strtok(line, sep); word; word = strtok(NULL, sep)){
		command -> sub_commands[i].line = strdup(word);
		i ++;
	}

	if (i < MAX_SUB_COMMANDS){
		command -> num_sub_commands = i;
	}else{
		command -> num_sub_commands = MAX_SUB_COMMANDS;
	}

}



void PrintCommand(struct Command *command){
	for(int i = 0; i < command -> num_sub_commands; i++){
		printf("sub_commands[%d]\n", i);
		PrintArgs(command -> sub_commands[i].argv);
		printf("Redirect stdin: %s\n", command -> stdin_redirect);
		printf("Redirect stdout: %s\n", command -> stdout_redirect);

		if(command -> background){
			printf("Background: Yes\n");
		}else{
			printf("Background: No\n");
		}
		
	}

}


void ReadArgs(char *in, char **argv, int size){

	char *sep = " ";
	char *word;
	int counter = 0;
	for(word = strtok(in, sep); word; word = strtok(NULL, sep)){

		*(argv + counter) = malloc(sizeof(char));	
		*(argv + counter) = strdup(word);
		counter ++;		
	}
	*(argv + counter) = malloc(sizeof(char));
	*(argv + counter)  = NULL;	
}

void PrintArgs(char **argv){
	int i = 0;
	for (i = 0; argv[i] != NULL; i ++){
		printf("argv[%d] = '%s'\n", i, argv[i]);
		free(argv[i]);
	}
	free(argv[i]);
}








