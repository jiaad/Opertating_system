#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
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

void new_line(int n) {
  int i;
  for (i = 0; i < n; i++) {
    write(1, "\n", 1);
  }
}

void print_char(int x, char *c) {
  int j;
  for (j = 0; j < x; j++) {
    write(1, c, 1);
  }
}

void print_line(int n) { int i; }
void print_box() {
  struct winsize ws;
  int i, j;
  int x, y;
  ioctl(0, TIOCGWINSZ, &ws);
  x = ws.ws_col / 3;
  y = ws.ws_row / 3;

  new_line(y);
  print_char(x, " ");
  print_char(1, ".");
  print_char(x, "-");
  print_char(1, ".");
  write(1, "\n", 1);
  for (i = 0; i < y; i++) {
    print_char(x, " ");
    write(1, "|", 1);
    print_char(x, " ");
    write(1, "|", 1);
    write(1, "\n", 1);
  }
  print_char(x, " ");
  print_char(1, "'");
  print_char(x, "-");
  print_char(1, "'");
  write(1, "\n", 1);
  new_line(y);
}
int main(void) {
  int a = 0;
  int first = 0;
  sigset_t old;
  struct sigaction act = {0};
  struct sigaction oact;
  act.sa_sigaction = &handler;
  sigaction(SIGWINCH, &act, &oact);
  int i = 0;
  print_box();
  while (1) {
    if (resized == 1) {
      print_box();
      resized = 0;
    }
  };

  return 0;
}
