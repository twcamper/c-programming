#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

typedef struct options
{
  bool number_all;
  bool number_non_blank;
} Options;


static void usage(char *pgm)
{
  fprintf(stderr, "Usage:\v$ %s [-nb] [file ...]\n", pgm);
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
  Options options = {false, false};
  int ch;

  while ((ch = getopt(*argc, *argv, "nb")) != EOF) {
    switch(ch) {
      case 'n':
        options.number_all = true;
        break;
      case 'b':
        options.number_non_blank = true;
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
  int lines, ch, next_char;
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
      if (o.number_all) {
        if (ftell(fp) == 1) {
          print_n(&lines);
        }
        if (ch == '\n') {
          putchar(ch);
          next_char = fgetc(fp);
          ungetc(next_char, fp);
          if (next_char != EOF)
            print_n(&lines);
          continue;
        }
      }
      if (o.number_non_blank) {
        next_char = fgetc(fp);
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
