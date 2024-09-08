#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <stdint.h>
#include "timing.h"

#define SLEEP_SEC 3
#define NUM_MULS 100000000
#define NUM_MALLOCS 100000
#define MALLOC_SIZE 1000
#define MIC_TO_MS(sec, usec) (sec) * 1e6 + (usec)

/**
* struct timeval {
             time_t       tv_sec;  long  seconds since Jan. 1, 1970
             suseconds_t  tv_usec; int   and microseconds
     };
*/
// TODO define this struct
struct profile_times {
  uint64_t real;
  uint64_t user;
  uint64_t sys;
};

// TODO populate the given struct with starting information
void profile_start(struct profile_times *t) {
  struct timeval start;
  struct rusage r_usage;
  gettimeofday(&start, NULL);
  time_t a;

  getrusage(0, &r_usage);

  t->sys = MIC_TO_MS(r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);
  t->real = MIC_TO_MS(start.tv_sec, start.tv_usec);
  t->user = MIC_TO_MS(r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec);
}

// TODO given starting information, compute and log differences to now
void profile_log(struct profile_times *t) {
  int cpu;
  struct profile_times tend;
  struct timeval end_real;
  struct rusage r_usage;
  gettimeofday(&end_real, NULL);
  getrusage(0, &r_usage);

  uint64_t real_time_end_ms = MIC_TO_MS(end_real.tv_sec, end_real.tv_usec);
  double real_time_ms = (real_time_end_ms - t->real) / 1e6;

  double diff_sys = (MIC_TO_MS(r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec) - t->sys) / 1e6;
  double diff_user = (MIC_TO_MS(r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec) - t->user) / 1e6;

  cpu = cpuid();
  printf("[pid: %d - cpu: %d] - user: %.9fs - sys: %.9fs - real: %.4fs\n",
         getpid(), cpu, diff_user, diff_sys, real_time_ms);
}

void extra_profile_log() {
  struct rusage r_usage;
  getrusage(0, &r_usage);
  printf("Context Switches: %ld\n", r_usage.ru_nvcsw);
  printf("Swaps: %ld\n", r_usage.ru_nswap);
}

int main(int argc, char *argv[]) {
  struct profile_times t;
  printf("Starting profile for %p\n", &t);
  // TODO profile doing a bunch of floating point muls
  float x = 1.0;
  profile_start(&t);
  for (int i = 0; i < NUM_MULS; i++)
    x *= 1.1;
  profile_log(&t);

  // TODO profile doing a bunch of mallocs
  profile_start(&t);
  void *p;
  for (int i = 0; i < NUM_MALLOCS; i++)
    p = malloc(MALLOC_SIZE);
  profile_log(&t);

  // TODO profile sleeping
  printf("[pid: %d]: sleeping for 3 seconds\n", getpid());
  profile_start(&t);
  sleep(SLEEP_SEC);
  profile_log(&t);
  extra_profile_log();
}
