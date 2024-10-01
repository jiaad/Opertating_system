#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 3

pid_t Fork(){
	pid_t p = fork();
	if(p < 0){
		fprintf(stderr, "FORK ERROR");
		exit(1);
	}
	return p;

}
int main(void){
	pid_t pid;
	int status;
	pid_t pids[3] = {0};
	int i;
	fprintf(stderr, "jiad is here\n");
	for(i = 0; i < 3; i++){
		if((pids[i] = Fork()) == 0){
			exit(100 + i);
		}
	}

	i = 0;
	while((pid = waitpid(pids[i], &status, 0)) > 0){
		if(WIFEXITED(status)){
		printf("MAIN PARENT: %d -> child %d terminated normally %d\n", getpid(), pid, WEXITSTATUS(status));
		
		} else {
			printf("child %d stopped abnormally\n", pid);
		
		}
		i++;
	}
	return 0;

}

