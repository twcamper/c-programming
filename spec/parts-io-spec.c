/* enable strdup() declaration in string.h */
#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  #define _BSD_SOURCE 1  /* for popen and pclose */
  #define CMD "md5sum"
#else
  #define CMD "md5"
#endif

#include <stdio.h>
#include "parts.h"
#include "test_runner.h"

#define PRINT(l,s) printf("%d: %s\n", (l), (s))
#define PT(l,p) printf("%d: %p\n", (l), (p))

#define MD5_LEN 32
static char *disk_checksum(char *filename)
{
  FILE *pipe;
  static char md5[MD5_LEN + 1];  /* static so we can return it */
  char cmd[255];

  sprintf(cmd, "%s %s | grep -Eo '[a-f0-9]{32}'", CMD, filename);

  if ((pipe = popen(cmd, "r")) == NULL)
    exit_error(errno, __FILE__, cmd);

  if (fgets(md5, MD5_LEN + 1, pipe) == NULL)
    print_error(errno, __FILE__, filename); /* don't exit: try to close the pipe */

  if (pclose(pipe) == EOF)
    exit_error(errno, __FILE__, filename);

  return md5;
}

int read_one_part_test(void)
{
  Parts db = restore("../data/one-part.dat");
  if (!db)
    print_error(errno, __FILE__, "read_one_part_test");
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
  Parts db = new_db(10);
  char *file = "../data/test.dat";
  char *md5;
  insert_part(db, set_part(13, "Bat fruit", 1, 1200));
  md5 = checksum(db);
  dump(file, db);
  _assert(strcmp(disk_checksum(file), md5) == 0);

  destroy_db(db);
  remove(file);
  return 0;
}
int read_two_parts_test(void)
{
  Parts db = restore("../data/two-parts.dat");
  if (!db)
    print_error(errno, __FILE__, "read_two_parts_test");
  _assert(size(db) == 2);

  Part p;
  _assert((p = find_part(db, 97)));
  _assert(get_part_price(p) == 123220);
  _assert(strcmp(checksum(db), "85a7c0923e8824238964f0e9353ee792") == 0);
  destroy_db(db);
  return 0;
}
int write_two_parts_test(void)
{
  Parts db = new_db(10);
  char *file = "../data/test.dat";
  char *md5;
  insert_part(db, set_part(13, "Bat fruit", 1, 1200));
  insert_part(db, set_part(19, "Bat Wing Hammer", 1000, 13200));
  md5 = checksum(db);
  dump(file, db);
  _assert(strcmp(disk_checksum(file), md5) == 0);

  destroy_db(db);
  remove(file);
  return 0;
}
int read_several_parts_test(void)
{
  Parts db = restore("../data/21-parts.dat"); 
  if (!db)
    print_error(errno, __FILE__, "read_several_parts_test");

  _assert(size(db) == 21);
  _assert(strcmp(checksum(db), "964934987768b516aac8163b47235358") == 0);
  destroy_db(db);
  return 0;
}
int write_several_parts_test(void)
{
  Parts db = new_db(10);

  insert_part(db, set_part(50, "manual key sort plucker", 11, 89));
  insert_part(db, set_part(40, "Parts List Catalog Index", 19, 0));
  insert_part(db, set_part(99, "funnel lip, unfinished", 1010, 4344));
  insert_part(db, set_part(512, "caterpiller feet, left", 1010, 99));
  insert_part(db, set_part(101, "Mental Health Services", 40, 100));
  insert_part(db, set_part(2, "Gas Ring, Municipal", 18, 214798900));

  char *md5 = checksum(db);
  char *file = "../data/test.dat";
  dump(file, db);
  _assert(strcmp(disk_checksum(file), md5) == 0);

  destroy_db(db);
  remove(file);
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
