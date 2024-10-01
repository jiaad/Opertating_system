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
		argv[0]= strdup("echo");
		argv[1]= strdup("hello");
		argv[2]= NULL;
		execvp(argv[0], argv);
	}else {
		printf("good bye [pid : %d] - fd : %d\n", getpid(), fd);
	}
	return 0;
}

