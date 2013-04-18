#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#ifdef DEBUG
#define PRINT_POS(l, c, n) fprintf(stderr, "%4d:\t%2ld\t'%d'\t%d\n", (l), ftell(fp), (c), (n))
#else
#define PRINT_POS(l, c, n)
#endif

typedef struct options
{
  bool number_all;
  bool number_non_blank;
  bool squeeze;
} Options;

static void usage(char *pgm)
{
  fprintf(stderr, "Usage:\v$ %s [-nbs] [file ...]\n", pgm);
}
static void print_e(int e, char *program, char *file)
{
  fprintf(stderr, "%s: %s: %s\n", program, strerror(e), file);
}

static void print_n(int *lines)
{
  printf("%5d  ", (*lines)++);
}
static Options process_options(int *argc, char **argv[])
{
  Options options = {false, false, false};
  int ch;

  while ((ch = getopt(*argc, *argv, "nbs")) != EOF) {
    switch(ch) {
      case 'n':
        options.number_all = true;
        break;
      case 'b':
        options.number_non_blank = true;
        break;
      case 's':
        options.squeeze = true;
        break;
      default:
        usage(*argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  if (options.number_non_blank)
    options.number_all = false;

  *argc -= optind;
  *argv += optind;

  return options;
}
int main(int argc, char *argv[])
{
  FILE *fp;
  int lines, ch, next_char, newlines = 0;
  char *program = argv[0];
  Options o = process_options(&argc, &argv);

  if (argc < 1) {
    usage(program);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < argc; i++) {
    if ((fp = fopen(argv[i], "rb")) == NULL) {
      print_e(errno, program, argv[i]);
      continue;
    }

    if (o.number_all || o.number_non_blank)
      lines = 1;

    for(;;) {
      if ((ch = fgetc(fp)) == EOF) {
        if (ferror(fp)) {
          print_e(errno, program, argv[i]);
        }
        break;
      }
      if (o.squeeze && ch == '\n') {
        newlines = 0;
        PRINT_POS(__LINE__, ch, newlines);
        while (ch == '\n') {
          newlines++;
          PRINT_POS(__LINE__, ch, newlines);
          if ((ch = fgetc(fp)) == EOF) {
            if (ferror(fp)) {
              print_e(errno, program, argv[i]);
              break;
            }
          }
          PRINT_POS(__LINE__, ch, newlines);
        }
        ungetc(ch, fp);
        PRINT_POS(__LINE__, ch, newlines);
        ch = '\n';
        if (newlines >= 2) {
          fseek(fp, -1, SEEK_CUR);
          PRINT_POS(__LINE__, ch, newlines);
        }
      }
      if (o.number_all) {
        if (ftell(fp) == 1) {
          print_n(&lines);
        }
        if (ch == '\n') {
          putchar(ch);
          if ((next_char = fgetc(fp)) == EOF) {
            if (ferror(fp)) {
              print_e(errno, program, argv[i]);
              break;
            }
          }
          ungetc(next_char, fp);
          if (next_char != EOF)
            print_n(&lines);
          continue;
        }
      }
      if (o.number_non_blank) {
        if ((next_char = fgetc(fp)) == EOF) {
          if (ferror(fp)) {
            print_e(errno, program, argv[i]);
            break;
          }
        }
        ungetc(next_char, fp);
        if (ch == '\n') {  /* this could be the first the line also */
          putchar(ch);
          if (next_char != EOF && next_char != '\n')
            print_n(&lines);
          continue;
        }
        if (ftell(fp) == 1 && next_char != '\n') {  /* first line, unless it's blank */
          print_n(&lines);
        }
      }
      putchar(ch);
    }

    fclose(fp);
  }
  return 0;
}
