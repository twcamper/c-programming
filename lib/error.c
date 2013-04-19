#include "error.h"

void invocation_error(char *program, char *usage)
{
  fprintf(stderr, "Usage: %s %s\n", program, usage);
  exit(1);
}

void memory_error(char *file, unsigned int line, const char *func)
{
  fprintf(stderr, "Memory Allocation Failure: %s:%d in function %s()\n", file, line, func);
  exit(EXIT_FAILURE);
}

void print_error(int e, char *program, char *s2)
{
  fprintf(stderr, "%s: %s: %s\n", program, s2, strerror(e));
}
void exit_error(int e, char *program, char *s2)
{
  print_error(e, program, s2);
  exit(EXIT_FAILURE);
}
