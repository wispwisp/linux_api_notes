#include "shmemtypes.h"


int do_server_work(key_t key, struct memory_block* mblock) {

  const char* msg = "Hello";
  strncpy(mblock->string, msg, MAXLEN);

  sleep(20); // time to run client :)

  // todo, for example with semaphores

  return EXIT_SUCCESS;
}


int do_client_work(key_t key, struct memory_block* mblock) {

  printf("Read from mem: %s\n", mblock->string);

  return EXIT_SUCCESS;
}
