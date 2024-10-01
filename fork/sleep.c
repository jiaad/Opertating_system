#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>






int main(void){
	printf("starting [pid: %d] \n", getpid());
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	}else if (rc == 0){
		close(STDOUT_FILENO);
		open("./output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		printf("inside pid [pid: %d] \n", getpid());
		char *chars[3];
		chars[0] = strdup("sleep");
		chars[1] = strdup("30000");
		chars[2] = NULL;
		// child (new process)	
		execvp(chars[0], chars);
		//execvp(chars[0], chars);
		printf("this should not print: i am inside child [pid: %d]\n", getpid());
	}else {
		int rc_wait = wait(NULL);
		printf("parent [pid: %d] [rc_wait: %d] child [pid: %d]\n", getpid(), rc_wait, rc);	
	}

	return 0;

}
