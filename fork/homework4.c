#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


int  main(void){
	int fd = open("jiad.txt", O_WRONLY | O_CREAT | O_TRUNC);
	printf("init [pid : %d] - fd at the beginning %d\n", getpid(), fd);
	int rc = fork();
	if(rc < 0){
		fprintf(stderr,"FORK FAILED");
		exit(1);
	}else if (rc == 0){
		char *argv[3];
		argv[0]= strdup("/bin/ls");
		argv[1]= strdup("-l");
		argv[2]= NULL;
		char *envp[1];
		argv[0]= NULL;
		// execl(argv[0], argv[1], (char *)0);
		// execlp(argv[0], argv[1], (char *)0);
		//execlp(argv[0], argv[1], (char *)0);
		// execv(argv[0], argv);
		// execvp(argv[0], argv);
		execvpe(argv[0], argv, envp);
	}else {
		printf("good bye [pid : %d] - fd : %d\n", getpid(), fd);
	}
	return 0;
}

