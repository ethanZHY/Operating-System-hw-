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
	};


void ReadCommand(char *line, struct Command *command);
void PrintCommand(struct Command *command);
void ReadArgs(char *in, char **argv, int size);
void PrintArgs(char **argv);

int main(){
	char line[200];
	printf("Please enter an input string\n");
	fgets(line, sizeof(line), stdin);

	struct Command *command = malloc(sizeof(struct Command));

	ReadCommand(line, command);
	PrintCommand(command);
	free(command);

	return 0;

}

void ReadCommand(char *line, struct Command *command){

	char *sep = "|";
	char *word;
	line[strlen(line)-1] = '\0';
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
	// read sub-commands
	for (int i = 0; i < command -> num_sub_commands; i++){
		ReadArgs(command->sub_commands[i].line, command->sub_commands[i].argv, MAX_ARGS);
	}

}
void PrintCommand(struct Command *command){
	for(int i = 0; i < command -> num_sub_commands; i++){
		printf("sub_commands[%d]\n", i);
		PrintArgs(command -> sub_commands[i].argv);
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


