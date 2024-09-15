#include <fcntl.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/resource.h>
#include <unistd.h>

/** struct rlimit {
 * 	rlim_t  rlim_cur;               current (soft) limit
 * 	rlim_t  rlim_max;                maximum value for rlim_cur
 * };
 **/

void s_overflow(int depth, long int start) {
  if (depth % 10000 == 0)
    printf("[pid: %d] %d -> %ld : (%p)\n", getpid(), depth,
           start - (long)&depth, &depth);
  return s_overflow(depth + 1, start);
}

void overflow_wrapper() {
  int depth = 0;
  s_overflow(depth, (long)&depth);
}

int main(void) {
  struct rlimit limit;
  getrlimit(RLIMIT_STACK, &limit);
  limit.rlim_cur = limit.rlim_max;
  limit.rlim_max = limit.rlim_max + 1000000;
  setrlimit(RLIMIT_STACK, &limit);
  printf("[pid %d] starting ------ curr: %llu - max: %llu\n", getpid(),
         limit.rlim_cur, limit.rlim_max);
  // for(;;);
  overflow_wrapper();
  return 0;
}
