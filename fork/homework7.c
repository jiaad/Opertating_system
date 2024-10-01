#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	printf("[parent pid: %d] hello\n", getpid());
	int pipefd[2];
	int tmpfd[2];
	char buf;
	pid_t cpid;
	if(pipe(pipefd) == -1){
		fprintf(stderr, "fildes is -1");	
		exit(1);
	}
	//	if(pipe(tmp_fd) == -1){
	//		fprintf(stderr, "tmp_fd is -1");		
	//		exit(1);
	//	}
	int rc = fork();

	if(rc < 0){
		fprintf(stderr, "FORK FAILED");
		exit(1);
	}else if (rc == 0){
			printf("inside child [pid: %d]\n", getpid());
			close(pipefd[1]);
			// write(STDOUT_FILENO, "\n", 1);
			while(read(pipefd[0], &buf, 1) > 0)
				write(STDOUT_FILENO, &buf, 1);
			write(STDOUT_FILENO, "\n", 1);
			close(pipefd[0]);
			exit(0);
	}else {
		// pid_t w = wait(&rc);
		printf("inside parent before terminate [pid: %d] [wait: %d]\n", getpid(), 1);
		close(pipefd[0]);
		write(pipefd[1], "jiad is here", 12);
		close(pipefd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	return 0;

}

