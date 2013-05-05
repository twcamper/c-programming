#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define LINE_MAX 255
int main(int argc, char *argv[])
{
  FILE *istream;
  int i;
  char *ch, line[LINE_MAX];
  char area_code[4], exchange[4], number[5];

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [input file]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((istream = fopen(argv[1], "r")) == NULL) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  while ((fgets(line, LINE_MAX, istream))) {
    for (ch = line; *ch && *ch != '\n';) {
      for (i = 0; i < 3; ch++)
        if (isdigit(*ch))
          area_code[i++] = *ch;
      area_code[i] = '\0';

      for (i = 0; i < 3; ch++)
        if (isdigit(*ch))
          exchange[i++] = *ch;
      exchange[i] = '\0';

      for (i = 0; i < 4; ch++)
        if (isdigit(*ch))
          number[i++] = *ch;
      number[i] = '\0';
    }

    printf("(%s) %s-%s\n", area_code, exchange, number);
  }
  if (ferror(istream))
    perror(argv[1]);

  if (fclose(istream) == EOF) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  return 0;
}
