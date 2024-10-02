
#define _GNU_SOURCE /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// char *parseline();
char *parseline();

int cs_strlen(char str[]) {
  int i;
  i = -1;
  while (str[++i] != '\0')
    ;
  return i;
}
void cs_split(char str[], char *res[]) {
  int i;
  int j;
  int len;
  int curr_idx;
  curr_idx = 0;
  len = cs_strlen(str);
  for (i = 0; i < len; i++) {
    if (str[i] == ' ')
      continue;
    char *temp = malloc(sizeof(char) * 10);
    temp[0] = str[i];
    for (j = i + 1; j <= len; j++) {
      if (str[j] == ' ' || j == len - 1) {
        res[curr_idx++] = strdup(temp);
        i = j;
        break;
      }
      temp[j - i] = str[j];
    }
  }
  res[curr_idx++] = NULL;
  res[curr_idx++] = NULL;
}

pid_t Fork() {
  pid_t p = fork();
  if (p < 0) {
    fprintf(stderr, "FORK ERROR");
    exit(1);
  }
  return p;
}

int main(int argc, char *argv[], char *envp[]) {
  while (1) {
    int i;
    printf("[%d]: ", getpid());
    fflush(NULL);
    pid_t pid;
    int status;
    char *str = parseline();
    pid = Fork();
    if (pid == 0) {
      char *splitted[4];
      cs_split(str, splitted);
      char *n_argv[4];
      printf("chlidren exec [%d]\n", getpid());
      for (int i = 0; i < 4; i++) {
        printf("----> [%s]\n", splitted[i]);
      }
      execve(splitted[0], splitted, envp);
      perror("echo test:"); /* execve() returns only on error */
      exit(EXIT_FAILURE);
    } else {
      // parent
      int status;
      pid_t w = wait(&status);
      printf("FINISHED with exit_s=%d status=%d\n", WEXITSTATUS(status),
             WIFEXITED(status));
      // exit(0);
    }
  }
  return 0;
}
