#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include <curses.h>

// struct sigaction {
//   union __sigaction_u __sigaction_u; /* signal handler */
//   sigset_t sa_mask;                  /* signal mask to apply */
//   int sa_flags;                      /* see signal options below */
// };
//
// union __sigaction_u {
//   void (*__sa_handler)(int);
//   void (*__sa_sigaction)(int, siginfo_t *, void *);
// };
//
// #define sa_handler __sigaction_u.__sa_handler
// #define sa_sigaction __sigaction_u.__sa_sigaction

void handler(int a, siginfo_t *siginfo, void *context) {
  printf("HANDLER %d\n", a);
  printf("HANDLER %d %d\n", siginfo->si_pid, siginfo->si_status);
}

int main(void) {
  int a = 0;
  struct sigaction act = {0};
  act.sa_sigaction = &handler;
  sigaction(SIGWINCH, &act, NULL);
  int ret = setupterm(NULL, STDOUT_FILENO, NULL);
  while(pause()){
    int width = tigetnum("cols");
    int height = tigetnum("lines");
    printf("FINISHED [%d] * [%d]\n", width, height);
  };

  return 0;
}
