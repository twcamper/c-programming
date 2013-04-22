/* enable strdup() declaration in string.h */
#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  #define CMD "md5sum"
#else
  #define CMD "md5"
#endif

#include <unistd.h>
#include "parts.h"
#include "test_runner.h"

#define PRINT(l,s) printf("%d: %s\n", (l), (s))

static char *disk_checksum(char *filename)
{
  int fd[2];
  if (pipe(fd) == -1) {
    fprintf(stderr, "Error creating pipe: %s:%d %s()\n", __FILE__, __LINE__, __func__);
    exit(EXIT_FAILURE);
  }
  pid_t pid = fork();
  if (pid == -1) {
    fprintf(stderr, "Error forking process: %s:%d %s()\n", __FILE__, __LINE__, __func__);
    exit(EXIT_FAILURE);
  }

  if (!pid) {/* child */
    dup2(fd[1], 1);  /* write end is now stdout */
    close(fd[0]);    /* read end is now closed  */
    
    char cmd[255];
    sprintf(cmd, "%s %s | grep -Eo '[a-f0-9]{32}'", CMD, filename);
    if (system(cmd) == -1) {
      fprintf(stderr, "Error executing child '%s': %s:%d %s()\n", CMD, __FILE__, __LINE__, __func__);
      exit(EXIT_FAILURE);
    }
  }
  /* parent */
  dup2(fd[0],0);     /* read end is now stdin */
  close(fd[1]);      /* parent needs no write end */
  
  static char md5[33];
  fgets(md5, 33, stdin);
  return md5;
}

int read_one_part_test(void)
{
  Parts db = restore("data/one-part.dat"); 
  Part p;
  _assert(size(db) == 1);
  _assert((p = find_part(db, 10)));
  _assert(get_part_number(p) == 10);
  _assert(get_part_on_hand(p) == 198);
  _assert(get_part_price(p) == 7000);
  _assert(strcmp(get_part_name(p), "Ball Washer") == 0);

  _assert(strcmp(checksum(db), "e6e10bb82703cc94788490dffe1d057c") == 0);
  destroy_db(db);
  return 0;
}
int write_one_part_test(void)
{
  _assert(strcmp(disk_checksum("data/has-blanks.txt"), "4f4fa4c16604bb8c3aacc104797d1d2a") == 0);
  return 0;
}
int read_two_parts_test(void)
{

  return 0;
}
int write_two_parts_test(void)
{

  return 0;
}
int read_several_parts_test(void)
{

  return 0;
}
int write_several_parts_test(void)
{

  return 0;
}
int read_many_parts_test(void)
{

  return 0;
}
int write_many_parts_test(void)
{

  return 0;
}
int all_tests(void)
{
  _run(read_one_part_test);
  _run(write_one_part_test);
  _run(read_two_parts_test);
  _run(write_two_parts_test);
  _run(read_several_parts_test);
  _run(write_several_parts_test);
  _run(read_many_parts_test);
  _run(write_many_parts_test);

  return 0;
}
