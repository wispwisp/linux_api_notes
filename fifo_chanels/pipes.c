#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#include <unistd.h>
#include <errno.h>

int main (int argc, char * argv[])
{
  int pipefd[2];
  if (pipe(pipefd) == -1)
    printf("pipe() failed, errno: %d", errno);

  pid_t pid = fork();
  if (pid > 0) {
    close(pipefd[0]);
    dup2(pipefd[1], 1);

    execve("/bin/netstat", NULL, NULL);
    close(pipefd[1]);
  }
  else if (pid == 0) {
    const int BUF_SZ = 1024;

    close(pipefd[1]);

    char buf[BUF_SZ];
    int len;
    while ((len = read(pipefd[0], buf, BUF_SZ)) != 0)
      write(2, buf, len);
    close(pipefd[0]);
  }
  else {
    perror("fork failed");
    exit(-1);
  }
  
  return 0 ;
}
