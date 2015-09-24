#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char ** argv)
{
  const int buf_sz = 1024;
  const char* str1 = "hello! how are you?";
  const char* str2 = "fine, u?";

  int sockets[2];
  char buf[buf_sz];

  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1) {
    perror("socketpair() failed");
    return EXIT_FAILURE;
  }

  pid_t pid = fork();
  if (pid > 0) {
    close(sockets[1]);

    // write:
    size_t len = strlen(str1);
    ssize_t nwrite = write(sockets[0], str1, len);
    if (nwrite != len)
      printf("not all bytes written\n");

    // read:
    ssize_t nread = read(sockets[0], buf, sizeof(buf));
    buf[nread] = 0;
    printf("%s\n", buf);

    close(sockets[0]);
  }
  else if (pid == 0) {
    close(sockets[0]);

    // read:
    ssize_t nread = read(sockets[1], buf, sizeof(buf));
    buf[nread] = 0;
    printf("%s\n", buf);

    // write:
    size_t len = strlen(str2);
    ssize_t nwrite = write(sockets[1], str2, len);
    if (nwrite != len)
      printf("not all bytes written\n");

    close(sockets[1]);
  }
  else {
    perror("fork failed");
    exit(-1);
  }

  return 0 ;
}
