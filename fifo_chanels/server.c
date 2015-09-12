#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main( int argc, char *argv[] ) {

  const char* const FIFO_FILE_NAME = "/tmp/my_fifofile";

  // mkfifo
  if (mkfifo(FIFO_FILE_NAME, 0600) == -1) {
    if (errno == EEXIST) {
      printf("fifo exists, unlinking...\n");
      unlink(FIFO_FILE_NAME);
    }
    else {
      perror("pipe() failed");
      exit(errno);
    }
  }

  // file
  FILE* f = fopen(FIFO_FILE_NAME, "w");
  if (f == NULL) { 
    perror("Error opening file");
    return -1;
  }

  // write
  char ch;
  do {
    ch = getchar();
    //putchar(ch);
    fputc(ch, f);
    if (ch == 10) fflush(f);
  } while (ch != 'q');

  fclose(f);
  unlink(FIFO_FILE_NAME);

  return 0;
}
