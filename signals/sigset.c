#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

extern const char* const sys_siglist[];

static void term_signal_handler (int signo)
{
  // not reentrant printf !
  printf("\nCaught(%d): %s\n", signo, sys_siglist[signo]);
  exit(EXIT_SUCCESS);
}

int main(void) {

  sigset_t set;

  // fill set, or empty set:
#ifdef MY_FILL_SET
  sigfillset(&set);
  sigdelset(&set, SIGTERM);
  sigprocmask(SIG_SETMASK, &set, 0);
#else
  sigemptyset(&set);
  sigaddset(&set, SIGTERM);
  sigaddset(&set, SIGINT); // ctr-c
  sigprocmask(SIG_BLOCK, &set, 0);
  // terminate this by: kill -s SIGKILL [pid]
#endif

  struct sigaction sa;
  sa.sa_handler = term_signal_handler;
  sigaction(SIGTERM, &sa, 0);

  printf("My pid is %i\n", getpid());
  printf("Waiting...\n");

  int sig;
  while(!sigwait(&set, &sig))
    printf("recieved: %s\n", sys_siglist[sig]);

  return EXIT_FAILURE;
}
