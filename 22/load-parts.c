#include <stdio.h>
#include "parts.h"

/*
OSX (Mach) limits (Snow Leopard)
  2147483584 = (2147483648 - 64) = 33554431* 64 bytes
  max that memory will hold before corruption
  1 more record is INT_MAX

Linux -- No limit found, but only tested up to 4GB ((67108864 + 1) * 64)
*/

int main(int argc, char *argv[])
{
  if (argc != 2)
    invocation_error(argv[0], "[filename]");

  Parts db;
  if ((db = restore(argv[1])) == NULL)
    print_error(errno, __FILE__, "NeverTheLess!");

  printf("%ld\n", size(db));
  /* printf("%s\n", checksum(db)); */
  print_part(last_part(db));

  return 0;
}
