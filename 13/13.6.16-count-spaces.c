#include <stdio.h>


int count_spaces(const char *s)
{
  int spaces = 0;

  while (*s)
    if (*s++ == ' ')
      spaces++;

  return spaces;
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    return 1;
  }

  printf("Spaces: %d\n", count_spaces(argv[1]));

  return 0;
}
