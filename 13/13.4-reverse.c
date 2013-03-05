#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(stderr, "Use more than 1 argument\n");
  }

  for (int i = argc - 1; i > 0; i--)
    printf("%s ", argv[i]);

  printf("\n");
  return 0;
}
