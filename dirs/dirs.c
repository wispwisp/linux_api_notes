#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>

int main(void) {

  const size_t max_path_size = 255;
  char path[max_path_size];

  if (!getcwd(path, max_path_size)) {
    perror("getcwd");
    exit(EXIT_FAILURE);
  }

  printf ("path: %s\n", path);

  // ***

  int dir_fd = open(".", O_RDONLY);
  if (dir_fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  const int dir_buf_size = 1024;
  char* dir_buf[dir_buf_size];
  ssize_t r = read(dir_fd, dir_buf, dir_buf_size);
  if (r < 0)
    perror("read dir");

  if (close(dir_fd)) {
    perror("close");
    exit(EXIT_FAILURE);
  }

  // ***

  DIR* dir = opendir(path);

  printf("Files:\n");
  struct dirent* entry;
  while ((entry = readdir(dir)) != NULL) {
    printf("\t%s,\t\tinode:%i, type:%i\n",
	   entry->d_name,
	   (int)entry->d_ino,
	   entry->d_type);    
  }

  if (closedir(dir) == -1)
    perror("close dir");

  return 0;
}
