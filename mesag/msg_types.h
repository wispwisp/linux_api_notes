#ifndef MSG_TYPES
#define MSG_TYPES

#define KEY 1174
#define MAXLEN 512

struct msg_t
{
  long mtype;
  int snd_pid;
  char body[MAXLEN];
};

#endif
