#define _GNU_SOURCE /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_LEN 100
// #define __MAIN__

char *parseline() {
  char *str = malloc(sizeof(char) * MAX_LEN);
  int res = read(0, str, 100);
  printf("-> %d\n", res);
  return str;
}
int parseline2(char buf[]) {
  int res = read(0, buf, 100);
  return res - 1;
}

/*
char *parseline(){
        char *str = malloc(sizeof(char) * MAX_LEN);
        int i;
        i = 0;
        while((str[i++] = getchar())){
                if(i > 0){
                        if(str[i - 1] == '\n')  break;
                }

        }
        return str;

}

*/
#ifdef __MAIN__
int main(void) {
  //	char *s = parseline();
  // char buf[MAX_LEN];
  char *buf = parseline();
  // for(int i = 0; i < count; i++){
  //		write(1, &buf[i], 1);
  //	}
  write(1, "\n", 1);
  printf("parse -> %s\n", buf);
  return 0;
}
#endif
