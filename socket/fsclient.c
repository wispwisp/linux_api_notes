#include "fsinclude.h"

int main(int argc, char ** argv)
{
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sock == -1) {
    perror("socket failed");
    return EXIT_FAILURE;
  }

  struct sockaddr srvr_name;
  memset(&srvr_name, 0, sizeof(struct sockaddr));
  srvr_name.sa_family = AF_UNIX;
  strncpy(srvr_name.sa_data, SOCK_NAME, sizeof(srvr_name.sa_data) - 1);

  char buf[BUF_SIZE];
  strcpy(buf, "Hello, Unix sockets!");

  ssize_t count = sendto(sock, buf, BUF_SIZE, 0, &srvr_name,
  		     strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family));

  printf("Передана строка: %s - что составляет %i байт\n", buf, count);

  return 0;
}
