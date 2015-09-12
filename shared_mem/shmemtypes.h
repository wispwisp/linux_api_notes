#ifndef SHMEM_TYPES
#define SHMEM_TYPES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>


#define FTOK_FILE_NAME "./server.exe"
#define MAXLEN 512


struct memory_block
{
  char string[MAXLEN];
};

int do_server_work(key_t, struct memory_block*);
int do_client_work(key_t, struct memory_block*);

#endif
