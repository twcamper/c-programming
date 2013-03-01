#include <stdio.h>

int main(void)
{

  char *p = "abc";

  putchar(*p);
  putchar(p);
  /* 13/13.3.2-pointer-to-string.c|9 col 3 warning| passing argument 1 of ‘putchar’ makes integer from pointer without a cast [enabled by default] */
  /* puts(*p); */
  /*
  Program received signal SIGSEGV, Segmentation fault.
    __strlen_sse2 () at ../sysdeps/x86_64/multiarch/../strlen.S:32
    32      ../sysdeps/x86_64/multiarch/../strlen.S: No such file or directory.
    (gdb) where
#0  __strlen_sse2 () at ../sysdeps/x86_64/multiarch/../strlen.S:32
#1  0x00007ffff7abd07b in _IO_puts (str=0x61 <Address 0x61 out of bounds>) at ioputs.c:37
#2  0x000000000040058b in main () at 13/13.3.2-pointer-to-string.c:11
    */

  puts(p);
  return 0;
}
