#include <stdio.h>

int main (int argc, char *argv[]) {

  const char* const FIFO_FILE_NAME = "/tmp/my_fifofile";

  FILE* f = fopen(FIFO_FILE_NAME, "r");

  char ch;
  do {
    ch = fgetc(f);
    putchar(ch);
  } while (ch != 'q');

  fclose(f);

  return 0;
}
