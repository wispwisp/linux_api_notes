#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#include "msg_types.h"

int main( int argc, char * argv[] ) {

  // get message queue
  int msgid = msgget(KEY, 0666);
  if (msgid == -1) {
    printf("Server is not running, errno [%i]", errno) ;
    return EXIT_FAILURE;
  }
  
  // pid
  pid_t pid = getpid();

  // mesage:
  struct msg_t message;
  message.mtype = 2;
  message.snd_pid = pid;

  // size of the rest of the message
  size_t msg_sz = sizeof(message) - sizeof(message.mtype);

  while (1) {
    // get msg body:
    printf("Client[pid=%i]>> ", pid);
    int i = 0;
    while ((i < (MAXLEN - 1)) && ((message.body[i++] = getchar()) !=  '\n'))
      ;
    message.body[i] = '\0';

    // send:
    msgsnd(msgid, &message, msg_sz, 0);

    if (!strcmp(message.body, "exit\n")) { // last '\n' because of terminating string with it
      printf("Exiting...\n");
      break;
    } // server responce:
    else {
      struct msg_t message_from_server;
      msgrcv(msgid,
	     &message_from_server,
	     sizeof(message_from_server) - sizeof(message_from_server.mtype),
	     1, 0);
      printf("Server (pid= %i) responded: %s",
	     message_from_server.snd_pid,
	     message_from_server.body);
    }
  }

  return EXIT_SUCCESS;
}
