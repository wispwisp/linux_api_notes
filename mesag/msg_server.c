#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#include "msg_types.h"

int main(int argc, char* argv[]) {

  // create message queue
  int msgid = msgget(KEY, 0666 | IPC_CREAT);
  if (msgid == -1) {
    printf("Error create message queue, errno: %d", errno);
    return EXIT_FAILURE;
  }

  // server response messgae
  struct msg_t message;
  message.mtype = 1;
  message.snd_pid = getpid();
  const char* response = "Recived\n";
  strncpy(message.body, response, MAXLEN);

  // size of the rest of the message
  size_t msg_sz = sizeof(message) - sizeof(message.mtype);

  // get messages from client:
  struct msg_t message_from_client;
  while (1) {
    msgrcv(msgid,
	   &message_from_client,
	   msg_sz, 2, 0);
    printf("Client (pid = %i) sent: %s",
	   message_from_client.snd_pid,
	   message_from_client.body);

    if (!strcmp(message_from_client.body, "exit\n")) {
      // last '\n' because of terminating string with it
      printf("Exiting...\n");
      break;
    }
    else { // response to client
      msgsnd(msgid, &message, msg_sz, 0);
    }
  }

  // удаляем очередь
  msgctl(msgid, IPC_RMID, 0);

  return EXIT_SUCCESS;
}
