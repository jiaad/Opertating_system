#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
int s_overflow(int i) {
  // printf("a: %d\n", i);
  FILE *fptr;
  fptr = fopen("filename.txt", "a");
  fprintf(fptr, "%p\n", &i);
  fclose(fptr);
  return s_overflow(i + 1);
}

int main(void) {
  sleep(2);
  FILE *fptr;
  fptr = fopen("filename.txt", "a");
  fprintf(fptr, "\nHi everybody!");
  fclose(fptr);
  s_overflow(1);

  // Open a file in append mode

  // Append some text to the file

  // Close the file
  return 0;
}
