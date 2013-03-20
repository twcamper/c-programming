#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void *malloc_or_die(size_t size)
{
  void *p;

  if ((p = malloc(size))== NULL) {
    fprintf(stderr, "Out of memory: %s %d (%s)\n", __FILE__, __LINE__, __func__);
    exit(1);
  }

  return p;
}
int main(void)
{

  char *s;
  for (int i = 0; i < 20000; i++)
  {
    s = malloc_or_die(INT_MAX);
    if ( i % 8 == 0)
      printf("%s\n", s);
    printf("%p\t",s);
  }
  return 0;
}
