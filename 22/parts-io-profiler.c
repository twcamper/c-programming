#include <stdio.h>
#include <time.h>
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
  if (argc != 3)
    invocation_error(argv[0], "[input file] [output file]");
  puts(argv[0]);

  Parts db;
  time_t  start_time  = time(NULL);
  clock_t start_clock = clock();
  if ((db = load_parts(argv[1])) == NULL)
    print_error( __FILE__, argv[1]);
  time_t  end_time  = time(NULL);
  clock_t end_clock = clock() - start_clock;

  printf("p %g:\tr %g:\tReading %ld from %s\n", end_clock / (double) CLOCKS_PER_SEC, difftime(end_time, start_time),  size(db), argv[1]);

  start_time  = time(NULL);
  start_clock = clock();
  if (dump(argv[2], db) != 0)
    print_error( __FILE__, argv[2]);
  end_time  = time(NULL);
  end_clock = clock() - start_clock;

  printf("p %g:\tr %g:\tWriting %s\n", end_clock / (double) CLOCKS_PER_SEC, difftime(end_time, start_time), argv[2]);
  puts("");
  return 0;
}
