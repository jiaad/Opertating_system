#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "csapp.h"
volatile long counter = 2;

// void handler(int a) {
//   sigset_t mask, prev_mask;
//   sigfillset(&mask);
//   sigprocmask(SIG_BLOCK, &mask, &prev_mask);
//   Sio_putl(--counter);
//   int olderrno = errno;
//   if ((waitpid(-1, NULL, 0)) < 0) {
//     write(0, "sig error\n", 10);
//     exit(0);
//   }
//   write(0, "Handler reaped chlid\n", 21);
//   sleep(1);
//   errno = olderrno;
// }
//

void handler2(int a) {
  int olderrno = errno;
  while ((waitpid(-1, NULL, 0)) > 0) {
    write(0, "Handler reaped chlid\n", 21);
  }
  if (errno != ECHILD)
    write(0, "sig error\n", 10);
  sleep(1);
  errno = olderrno;
}

int main(void) {
  int i, n;
  char buf[100];

  if (signal(SIGCHLD, handler2) == SIG_ERR) {
    fprintf(stderr, "SIGNAL ERROR");
    exit(0);
  }

  for (i = 0; i < 3; i++) {
    if (fork() == 0) {
      printf("hello from [%d] - to [%d]\n", getpid(), getppid());
      exit(100 + i);
    }
  }

  if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0) {
    fprintf(stderr, "READ ERROR");
    exit(0);
  }
  while (1)
    ;
  exit(0);

  return 0;
}
