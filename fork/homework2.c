#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int  main(void){
	int fd = open("jiad.txt", O_WRONLY | O_CREAT | O_TRUNC);
	printf("init [pid : %d] - fd at the beginning %d\n", getpid(), fd);
	int rc = fork();
	if(rc < 0){
		fprintf(stderr,"FORK FAILED");
		exit(1);
	}else if (rc == 0){
		write(fd, "hello", 5);
		printf("inside child [pid : %d] - fd : %d\n", getpid(), fd);
	}else {
		write(fd, "jiaad", 5);
		printf("finish [pid : %d] - fd : %d\n", getpid(), fd);
	}
	return 0;
}

