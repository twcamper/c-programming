/* enable strdup() declaration in string.h */
#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  #define CMD "md5sum"
#else
  #define CMD "md5"
#endif

#include <stdio.h>
#include "parts.h"
#include "test_runner.h"

#define PRINT(l,s) printf("%d: %s\n", (l), (s))

#define MD5_LEN 32
static char *disk_checksum(char *filename)
{
  FILE *pipe;
  static char md5[MD5_LEN + 1];  /* static so we can return it */
  char cmd[255];

  sprintf(cmd, "%s %s | grep -Eo '[a-f0-9]{32}'", CMD, filename);

  if ((pipe = popen(cmd, "r")) == NULL) {
    fprintf(stderr, "popen(%s, \"r\")\n %s:%d %s()\n", cmd, __FILE__, __LINE__, __func__);
    exit(EXIT_FAILURE);
  }

  if (fgets(md5, MD5_LEN + 1, pipe) == NULL)
    print_error(errno, __FILE__, filename);

  if (pclose(pipe) == EOF)
    print_error(errno, __FILE__, filename);

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
