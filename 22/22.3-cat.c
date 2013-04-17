#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static void print_e(int e, char *program, char *file)
{
  fprintf(stderr, "%s: %s: %s\n", program, strerror(e), file);
}

int main(int argc, char *argv[])
{
  FILE *fp;
  int ch;

  if (argc < 2) {
    fprintf(stderr, "Usage:\v$ %s <files>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "rb")) == NULL) {
      print_e(errno, argv[0], argv[i]);
      continue;
    }

    for(;;) {
      if ((ch = fgetc(fp)) == EOF) {
        if (ferror(fp)) {
          print_e(errno, argv[0], argv[i]);
        }
        break;
      }
      putchar(ch);
    }

    fclose(fp);
  }
  return 0;
}
