#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

extern const char* const sys_siglist[];

static void signal_handler (int signo)
{
  // not reentrant printf !
  printf("\nCaught(%d): %s\n", signo, sys_siglist[signo]);
  exit(EXIT_SUCCESS);
}

int main (void) {
  if (signal(SIGINT, signal_handler) == SIG_ERR) {
    perror("Cannot handle SIGINT!");
    exit(EXIT_FAILURE);
  }

  if (signal(SIGTERM, signal_handler) == SIG_ERR) {
    perror("Cannot handle SIGTERM!");
    exit(EXIT_FAILURE);
  }

  // etc...

  for(;;)
    pause();

  return 0;
}
