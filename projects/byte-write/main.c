#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void byte_write(int fd) {
  FILE *fptr;
  fptr = fopen("test.txt", "a");
  fprintf(fptr, "a");
  fclose(fptr);
  printf("\nwriting a byte to a file\n");
}

int main(void) {
  struct stat buf;
  // FILE *fptr;
  // fptr = fopen("test.txt", "w");
  int fd;
  fd = open("./test.txt", O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "There is an error\n");
    exit(1);
  }
  fstat(fd, &buf);
  printf("[pid %d] fd: %d -> file size: %lld\n", getpid(), fd, buf.st_size);
  while (1) {
    byte_write(fd);
    fstat(fd, &buf);
    printf("[pid %d] fd: %d -> file size: %lld\n", getpid(), fd, buf.st_size);
    sleep(1);
  }
  close(fd);
  // fprintf(fptr, "a");
  return 0;
}