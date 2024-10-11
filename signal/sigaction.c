#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <term.h>
#include <unistd.h>
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
volatile sig_atomic_t resized = 0;

void handler(int a, siginfo_t *siginfo, void *context) {
  // int ret = setupterm(NULL, STDOUT_FILENO, NULL);
  // int width = tigetnum("cols");
  // int height = tigetnum("lines");
  // printf("HANDLER %d\n", a);
  // printf("HANDLER %d %d\n", siginfo->si_pid, siginfo->si_status);
  // printf("DIMENSION [%d] * [%d]\n", width, height);
  resized = 1;
}

int main(void) {
  int a = 0;
  sigset_t old;
  struct sigaction act = {0};
  struct sigaction oact;
  act.sa_sigaction = &handler;
  sigaction(SIGWINCH, &act, &oact);
  int ret = setupterm(NULL, STDOUT_FILENO, NULL);
  int i = 0;
  struct winsize ws;
  while (1) {
    if (resized == 1) {
      ioctl(0, TIOCGWINSZ, &ws);
      int width = tigetnum("cols");
      int height = tigetnum("lines");
      printf("FINISHED [%d] * [%d] , [%d]\n", ws.ws_col, ws.ws_row, i);
      resized = 0;
    }
  };

  return 0;
}
