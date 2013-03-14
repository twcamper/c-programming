#include "error.h"

void invocation_error(char *program, char *usage)
{
  fprintf(stderr, "Usage:\v$ %s %s\n", program, usage);
  exit(1);
}
