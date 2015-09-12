#include "shmemtypes.h"

int main(int argc, char * argv[]) {

  // Generate key using file name and 8 significant bits from second arg
  key_t key = ftok(FTOK_FILE_NAME, 1); // defined in shmemtypes.h
  if (key == -1) {
    printf("Failed to generate unique key. Server compiler with a wrong name?\n");
    return EXIT_FAILURE;
  }

  // get id of shared memory segment associated wih key
  int shmid = shmget(key, sizeof(struct memory_block), 0666);
  if (shmid == -1) {
    printf("Server is not running!\n");
    return EXIT_FAILURE;
  }

  // Attache the shared memory segment to addres space
  struct memory_block* mblock = (struct memory_block *) shmat(shmid, 0, 0);
  if (mblock == (void *)-1) {
    printf("Failed to attach shared memory segment, errno: %s", strerror(errno));
    return EXIT_FAILURE;
  }

  // .. server-client communication with sem
  if (do_client_work(key, mblock))
    return EXIT_FAILURE;

  // detach shared memory segment from process adr space
  int detach_res = shmdt((void *) mblock);
  if (detach_res == -1) {
    printf("Failed to detach shared memory segment, errno: %s", strerror(errno));
    return EXIT_FAILURE;
  }

  printf("Client exits\n");
  return EXIT_SUCCESS;
}
