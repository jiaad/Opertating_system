#ifndef __TIMING__
#ifdef __APPLE__
#include <cpuid.h>
extern inline int cpuid() {
  unsigned regs[4];
  __cpuid_count(1, 0, regs[0], regs[1], regs[2], regs[3]);

  return regs[1] >> 24;
}
#elif __linux
#define _GNU_SOURCE
#include <sched.h>
int cpuid() { return sched_getcpu(); }
#endif
int cupid();
#endif
