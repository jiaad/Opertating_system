#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int  main(void){
	int x = 100;
	printf("init [pid : %d] - x at the beginning %d\n", getpid(), x);
	int rc = fork();
	x = 100;
	if(rc < 0){
		fprintf(stderr,"FORK FAILED");
		exit(1);
	}else if (rc == 0){
		x = -1;
		printf("inside child [pid : %d] - x is %d \n", getpid(), x);
	}else {
		printf("finish [pid : %d] - x is %d \n", getpid(), x);
	}
	return 0;
}

