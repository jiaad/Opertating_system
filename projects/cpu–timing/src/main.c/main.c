#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./../timing.h"

#define SLEEP_SEC 3
#define NUM_MULS 100000000
#define NUM_MALLOCS 100000
#define MALLOC_SIZE 1000

int main(int argc, char *argv[]) {
  struct profile_times t;
  printf("Starting profile for %p\n", &t);

  float x = 1.0;
  profile_start(&t);
  for (int i = 0; i < NUM_MULS; i++)
    x *= 1.1;
  profile_log(&t);

  profile_start(&t);
  void *p;
  for (int i = 0; i < NUM_MALLOCS; i++)
    p = malloc(MALLOC_SIZE);
  profile_log(&t);

  printf("[pid: %d]: sleeping for 3 seconds\n", getpid());
  profile_start(&t);
  sleep(SLEEP_SEC);
  profile_log(&t);
  extra_profile_log();
}
