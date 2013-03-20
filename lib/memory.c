#include "memory.h"
void *malloc_or_die(size_t size)
{
  void *p;

  if ((p = malloc(size))== NULL)
    fprintf(stderr, "Out of memory: %s %d (%s)\n", __FILE__, __LINE__, __func__);

  return p;
}

