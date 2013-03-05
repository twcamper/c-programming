#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(stderr, "Use more than 1 argument\n");
  }

  int sum = 0;
  for (int i = 1; i < argc; i++) sum += atoi(argv[i]);
  /* for (char **i = &argv[1]; i < argv + argc; i++) sum += atoi(*i); */

  printf("Total: %d\n", sum);
  return 0;
}
