#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	printf("[parent pid: %d] hello\n", getpid());
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "FORK FAILED");
		exit(1);
	}else if (rc == 0){
		printf("inside child [pid: %d]\n", getpid());
	}else {
		// pid_t w = wait(&rc);
		pid_t w = waitpid(-1, &rc, 0);
		printf("inside parent before terminate [pid: %d] [wait: %d]\n", getpid(), w);
	}
	return 0;

}

