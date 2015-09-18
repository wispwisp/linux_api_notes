#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <linux/limits.h>

int do_daemon_work(){

  const char* path = "/tmp/daemonPostMortum";

  unlink(path);

  FILE* file = fopen(path, "w");
  fprintf(file, "I am daemon. Lived and die. PostMortum:\n");
  fprintf(file, "pid: %lld\n", (long long int)getpid());
  fclose(file);

  return 0;
}

int main (void)
{
  pid_t pid = fork();
  if (pid == -1)
    return -1;
  else if (pid != 0)
    exit(EXIT_SUCCESS);

  // daemon

  // separate session
  if (setsid() == -1)
    return -1;

  // root dir
  if (chdir("/") == -1)
    return -1;

  for (int i = 0; i < 3; i++)
    close(i);

  // redirect fd's 0,1,2 to /dev/null
  open("/dev/null", O_RDWR); // stdin, `cause all fds cloesd previously
  if (dup(0) == -1) // stdout
    return -1;
  if (dup(0) == -1) // stderror
    return -1;

  return do_daemon_work();
}
