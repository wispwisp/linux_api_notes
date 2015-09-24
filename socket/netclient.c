#include "netinclude.h"

#include <netdb.h>

int main(int argc, char ** argv)
{
  if (argc < 3) {
    fprintf(stderr,"usage: %s <hostname> <port_number>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("socket() failed");
    return EXIT_FAILURE;
  }

  struct hostent* server = gethostbyname(argv[1]);
  if (server == NULL) {
    perror("Host not found");
    close(sock);
    return EXIT_FAILURE;
  }

  struct sockaddr_in serv_addr;
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
  int port = atoi(argv[2]);
  serv_addr.sin_port = htons(port);


  if (connect(sock, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
    perror("connect() failed");
    close(sock);
    return EXIT_FAILURE;
  }

  char buf[BUF_SIZE];
  memset(buf, 0, BUF_SIZE);

  // todo: nice input
  printf(">");
  if (!fgets(buf, BUF_SIZE-1, stdin))
    perror("fgets() no string input");

  size_t input_str_len = strlen(buf);
  ssize_t nwrite = write(sock, buf, input_str_len);
  if (input_str_len != nwrite)
    printf("write incomplete\n");

  ssize_t nread = read(sock, buf, BUF_SIZE-1);
  if (nread == -1) {
    perror("read error");
  } else {
    buf[nread] = 0;
    printf("%s\n", buf);
  }

  close(sock);

  return 0;
}
