#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

	char str[300];
	while(1){
		printf("$");
		fgets(str, sizeof(str), stdin);
		str[strlen(str)-1]='\0';
		printf("%s\n", str);
	}
	

	return 0;
}