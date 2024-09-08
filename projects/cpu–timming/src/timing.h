#ifndef __TIMING__
#include <inttypes.h>
#include <sys/time.h>
#ifdef __APPLE__
#include <cpuid.h>
static inline int cpuid() {
  unsigned regs[4];
  __cpuid_count(1, 0, regs[0], regs[1], regs[2], regs[3]);

  return regs[1] >> 24;
}
#elif __linux
#define _GNU_SOURCE
#include <sched.h>
int cpuid() { return sched_getcpu(); }
#else
int cpuid() { return -1; }
#endif

struct profile_times {
  uint64_t real;
  uint64_t user;
  uint64_t sys;
};

void profile_start(struct profile_times *t);

void profile_log(struct profile_times *t);

void extra_profile_log();

static inline int cpuid();
#endif
