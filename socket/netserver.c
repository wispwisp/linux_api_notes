#include "netinclude.h"

int main(int argc, char ** argv)
{
  if (argc < 2) {
    fprintf(stderr, "usage: %s <port_number>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("socket() failed");
    return EXIT_FAILURE;
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  int port = atoi(argv[1]);
  serv_addr.sin_port = htons(port);

  if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
    perror("bind() failed");
    close(sock);
    return EXIT_FAILURE;
  }

  if (listen(sock, 1) == -1) {
    perror("listen() failed");
    close(sock);
    return EXIT_FAILURE;
  }

  struct sockaddr_in cli_addr;
  socklen_t cli_len = sizeof(cli_addr);
  int newsock = accept(sock, (struct sockaddr *) &cli_addr, &cli_len);
  if (newsock == -1) {
    printf("accept() failed: %d\n", errno);
    close(sock);
    return EXIT_FAILURE;
  }

  char buf[BUF_SIZE];
  memset(buf, 0, BUF_SIZE);

  ssize_t nread = read(newsock, buf, BUF_SIZE-1);
  if (nread == -1) {
    perror("read error");
  } else {
    buf[nread] = 0;
    printf("MSG: %s\n", buf);
    ssize_t nwrite  = write(newsock, "OK", 2);
    if (nwrite < 2)
      printf("write incomplete\n");
  }

  close(newsock);
  close(sock);

  return 0;
}
