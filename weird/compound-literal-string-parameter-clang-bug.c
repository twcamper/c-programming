#include <stdio.h>

/* 
 * $ clang --version
 * clang version 3.1 (branches/release_31)
 * Target: x86_64-apple-darwin10.8.0
 * Thread model: posix
 */


/*
 * output without call to printf from within main:
 *
 * $ weird/compound-literal-string-parameter-clang-bug | xxd
 * 0000000: 0d0a 20e7 bf5f ff7f                      .. .._..
 * $ weird/compound-literal-string-parameter-clang-bug | wc
 *        1       1       8
 */

/* works fine compiled with i686-apple-darwin10-gcc-4.2.1 (GCC) 4.2.1 */
void  write_dos_newline()
{
  printf("%s", (char[2]){0x0D, 0x0A});
}


int main(void)
{
  /* call from main works as expected */
  printf("%s", (char[2]){0x0D, 0x0A});
  /* call via function appends 6 bytes of junk */
  write_dos_newline();
  return 0;
}
