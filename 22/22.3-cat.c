#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

typedef struct options
{
  bool number;
} Options;


static void usage(char *pgm)
{
  fprintf(stderr, "Usage:\v$ %s [-n] [file ...]\n", pgm);
}
static void print_e(int e, char *program, char *file)
{
  fprintf(stderr, "%s: %s: %s\n", program, strerror(e), file);
}

static Options process_options(int *argc, char **argv[])
{
  Options options = {false};
  int ch;

  while ((ch = getopt(*argc, *argv, "n")) != EOF) {
    switch(ch) {
      case 'n':
        options.number = true;
        break;
      default:
        usage(*argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  *argc -= optind;
  *argv += optind;

  return options;
}
int main(int argc, char *argv[])
{
  FILE *fp;
  int ch;
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

    for(;;) {
      if ((ch = fgetc(fp)) == EOF) {
        if (ferror(fp)) {
          print_e(errno, program, argv[i]);
        }
        break;
      }
      putchar(ch);
    }

    fclose(fp);
  }
  return 0;
}
