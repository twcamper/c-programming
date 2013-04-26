#include <stdio.h>
#include "parts.h"

/*
2147483584 = (2147483648 - 64) = 33554431* 64 bytes
max that memory will hold before corruption
1 more record is INT_MAX, which must be the max addressable memory per process
*/

int main(int argc, char *argv[])
{
  if (argc != 2)
    invocation_error(argv[0], "[filename]");

  Parts db;
  if ((db = restore(argv[1])) == NULL)
    print_error(errno, __FILE__, "NeverTheLess!");

  printf("%ld\n", size(db));
  printf("%s\n", checksum(db));
  printf("%s\n", get_part_name(last_part(db)));


  return 0;
}
