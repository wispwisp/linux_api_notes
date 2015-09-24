#include "fsinclude.h"

int main(int argc, char ** argv)
{
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sock == -1) {
    perror("socket failed");
    return EXIT_FAILURE;
  }

  // server struct prepare
  struct sockaddr srvr_name;
  memset(&srvr_name, 0, sizeof(struct sockaddr));
  srvr_name.sa_family = AF_UNIX;
  strncpy(srvr_name.sa_data, SOCK_NAME, sizeof(srvr_name.sa_data) - 1);

  // bind
  if (bind(sock, &srvr_name, sizeof(struct sockaddr)) == -1) {
    perror("bind failed");
    return EXIT_FAILURE;
  }

  // recive from client
  char buf[BUF_SIZE];
  struct sockaddr rcvr_name;
  socklen_t namelen = sizeof(rcvr_name);
  ssize_t bytes = recvfrom(sock,
			   (void*)buf,
			   (size_t)BUF_SIZE-1,
			   0, &rcvr_name, &namelen);
  if (bytes < 0) {
    perror("recvfrom failed");
    return EXIT_FAILURE;
  }

  buf[bytes] = 0;
  rcvr_name.sa_data[namelen] = 0;
  printf("Client sent: %s\n", buf);

  close(sock);
  unlink(SOCK_NAME);
}
