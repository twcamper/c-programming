#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BLOCK_SIZE 4096

static void exit_error(char *s)
{
  perror(s);
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[])
{
  int fd_source, fd_target, rc = 0;
  ssize_t n_read;
  unsigned char buffer[BLOCK_SIZE] = {0};
  struct stat source_stat;

  if (argc != 3) {
    fprintf(stderr, "usage %s source_file target_file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (stat(argv[1], &source_stat) != 0)
    exit_error("stat");

  if ((fd_source = open(argv[1], O_RDONLY)) == -1)
    exit_error(argv[1]);

  if ((fd_target = open(argv[2], O_WRONLY|O_CREAT)) == -1) {
    perror(argv[2]);
    if (close(fd_source) == -1)
      perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  if (chmod(argv[2], source_stat.st_mode) == -1)
    exit_error("chmod");

  while ((n_read = read(fd_source, buffer, BLOCK_SIZE)) > 0)
    if (write(fd_target, buffer, n_read) == -1)
      exit_error(argv[2]);
  if (n_read == -1)
    exit_error(argv[1]);

  if (close(fd_source) == -1) {
    perror(argv[1]);
    rc = -1;
  }

  if (close(fd_target) == -1) {
    perror(argv[2]);
    rc = -1;
  }

  return rc;
}
