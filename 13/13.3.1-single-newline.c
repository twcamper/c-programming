#include <stdio.h>

int main(void)
{
  printf("%c", '\n');
  printf("%c", "\n");
  /* printf("%s", '\n'); */
  /*
Program received signal SIGSEGV, Segmentation fault.
  0x00007ffff7a98cba in _IO_vfprintf_internal (s=0x7ffff7dd77a0, format=0x400701 "%s", ap=0x7fffffffe150) at vfprintf.c:1623
  1623    vfprintf.c: No such file or directory.
  (gdb) where
#0  0x00007ffff7a98cba in _IO_vfprintf_internal (s=0x7ffff7dd77a0, format=0x400701 "%s", ap=0x7fffffffe150) at vfprintf.c:1623
#1  0x00007ffff7aa147a in __printf (format=0x400702 "s") at printf.c:35
#2  0x00000000004005d6 in main () at 13/13.3.1-single-newline.c:7
*/



  printf("%s", "\n");
  /* printf('\n'); */
  /*
  Program received signal SIGSEGV, Segmentation fault.
    strchrnul () at ../sysdeps/x86_64/strchrnul.S:34
    34      ../sysdeps/x86_64/strchrnul.S: No such file or directory.
    (gdb) where
#0  strchrnul () at ../sysdeps/x86_64/strchrnul.S:34
#1  0x00007ffff7a9671f in __find_specmb (format=<optimized out>) at printf-parse.h:99
#2  _IO_vfprintf_internal (s=0x7ffff7dd77a0, format=0xa <Address 0xa out of bounds>, ap=0x7fffffffe150) at vfprintf.c:1328
#3  0x00007ffff7aa147a in __printf (format=0xffffffff <Address 0xffffffff out of bounds>) at printf.c:35
#4  0x00000000004005db in main () at 13/13.3.1-single-newline.c:21
    */
  putchar('\n');
  putchar("\n");
  /* 13/13.3.1-single-newline.c|34 col 3 warning| passing argument 1 of ‘putchar’ makes integer from pointer without a cast [enabled by default] */

  return 0;
}
