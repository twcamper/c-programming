#include "error.h"

void invocation_error(char *program, char *usage)
{
  fprintf(stderr, "Usage:\v$ %s %s\n", program, usage);
  exit(1);
}

void memory_error(char *file, unsigned int line, const char *func)
{
  fprintf(stderr, "Memory Allocation Failure: %s:%d in function %s()\n", file, line, func);
  exit(EXIT_FAILURE);
}
