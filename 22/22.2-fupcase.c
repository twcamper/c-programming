#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int ch;
  FILE *fp;
  if (argc != 2) {
    fprintf(stderr, "Usage:\v %s filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Error opening file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  while ((ch = fgetc(fp)) != EOF)
    putchar(toupper(ch));

  fclose(fp);
  return 0;
}
