#include <stdio.h>

int main(int argc, char *argv[], char *envp[]){
	int i;
	printf("Bro said 🤣 \n");

	for(i = 0; i < argc; i++){
		printf("ARGV[%d] - %s\n", i, argv[i]);
	}
	/*
	printf("\nPRINTING ENVP\n");

	i = 0;
	while(envp[i] != NULL){
		printf("ENVP[%d] - %s\n", i, envp[i]);
		i++;
	}
	*/

}
