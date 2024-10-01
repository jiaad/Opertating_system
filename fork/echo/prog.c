
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//char *parseline();
char* parseline();


int cs_strlen(char str[]){
	int i;
	i = -1;
	while(str[++i] != '\0');
	return i;

}
void cs_split(char str[], char *res[]){
        int i;
        int j;
        int len;
        int curr_idx;
        curr_idx = 0;

        len = cs_strlen(str);

        for(i = 0; i < len; i++){
                if(str[i] == ' ') continue;
                char *temp = malloc(sizeof(char) * 10);
                temp[0] = str[i];
                for(j = i + 1; j < len; j++){
                        if(str[j] == ' '){
                                res[curr_idx++] = temp;
                                i = j;
                                break;
                        }
                        temp[j-i] = str[j];
                }
        }
	res[curr_idx] = NULL;

}
pid_t Fork(){
	pid_t p = fork();
	if(p < 0){
		fprintf(stderr, "FORK ERROR");
		exit(1);
	}
	return p;

}
int main(int argc, char *argv[], char *envp[]){
	char *splitted[100];
	int i;
	printf("[%d]: ", getpid());
	fflush(NULL);
	pid_t pid;
	int status;
	char *str = parseline();
	cs_split(str, splitted);
	for(i = 0; splitted[i] != NULL; i++){
		printf("------ %s\n", splitted[i]);
	}
	pid = Fork();
	if(pid == 0){
		char *n_argv[2];
		n_argv[0] = str;
		n_argv[1] = NULL;
		// execve("./cs_echo", n_argv, envp);
		write(1, "execve", 6);
		write(1, "\n", 1);
		execve("/bin/ls", splitted, envp);
	}else {
		// parent
		pid_t w = wait(NULL);
		printf("FINISHED\n");
		exit(0);
	}
	return 0;

}

