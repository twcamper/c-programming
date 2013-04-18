#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

static void print_e(int e, char *program, char *file)
{
  fprintf(stderr, "%s: %s: %s\n", program, file, strerror(e));
}
static void print_totals(long int c, long int w, long int l)
{
  printf("%7ld  %9ld  %9ld", l, w, c);
}
static void wc(FILE *stream, long *characters, long *words, long *lines)
{
  int ch;
  bool in_token = false;
  *characters = 0, *words = 0, *lines = 0;
  while ((ch = fgetc(stream)) != EOF) {
    (*characters)++;
    if (ch == '\n')
      (*lines)++;

    if (isspace(ch)) {
      if (in_token)
        (*words)++;  /* first char after the token */
      in_token = false;
    } else
      in_token = true;

  }
  if (ferror(stream)) {
    print_e(errno, __FILE__, "wc");
    exit(EXIT_FAILURE);
  }
  if (in_token)
    (*words)++;  /* last char of last token followed by EOF */
}

int main(int argc, char *argv[])
{
  long characters, words, lines;

  if (argc == 1) {
    wc(stdin, &characters, &words, &lines);
    print_totals(characters, words, lines);
    putchar('\n');
    return 0;
  }

  long c_total = 0, w_total = 0, l_total = 0;
  FILE *fp;

  for (int i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "rb")) == NULL)
      print_e(errno, argv[0], argv[i]);

    wc(fp, &characters, &words, &lines);

    if (fclose(fp) == EOF)
      print_e(errno, argv[0], argv[i]);

    print_totals(characters, words, lines);
    printf("\t%s\n", argv[i]);
    if (argc > 2)
      c_total += characters; w_total += words; l_total += lines;
  }
  if (argc > 2) {
    print_totals(c_total, w_total, l_total);
    printf("\ttotal\n");
  }

  return 0;
}
