#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  struct kevent event;
  struct kevent tevent;
  int fd, kq, ret;

  fd = open("test.txt", O_RDONLY);
  printf("fd is: %d\n",fd);
  if (fd == -1) {
    err(EXIT_FAILURE, "Bad file descriptor %d", fd);
  }

  kq = kqueue();
  if (kq == -1) {
    err(EXIT_FAILURE, "kqueue() falied");
  }

  EV_SET(&event, fd, EVFILT_VNODE, EV_ADD | EV_CLEAR, NOTE_WRITE, 0, NULL);

  ret = kevent(kq, &event, 1, NULL, 0, NULL);
  if (ret == -1) {
    err(EXIT_FAILURE, "kevent register failed");
  }

  for (;;) {
    ret = kevent(kq, NULL, 0, &tevent, 1, NULL);

    if (ret == -1) {
      err(EXIT_FAILURE, "kevent register failed");
    } else {
      if (tevent.flags & EV_ERROR) {
        errx(EXIT_FAILURE, "Event error: %s", strerror(event.data));
      } else {
        printf("Something was written in test.txt\n");
      }
    }
  }
  (void)close(fd);
  (void)close(kq);
  return 0;
}
