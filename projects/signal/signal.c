#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>

void handler(int a) {
  if (a == SIGWINCH)
    printf("WINDOW SIZE CHANGED\n");
}

int main(void) {
  signal(SIGWINCH, handler);
  while(pause());
  return 0;
}
