#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_MAX 1024

int main(int argc, char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Usage: %s [input file] [output file]", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *iname  = argv[1];
  char *oname =  argv[2];;
  FILE *istream, *ostream;
  unsigned char buffer[BUFFER_MAX];
  int ch, next = 0, newline = '\0', rc = 0;
  size_t i = 0;

  if ((istream = fopen(iname, "rb")) == NULL) {
    perror(iname);
    exit(EXIT_FAILURE);
  }

  if ((ostream = fopen(oname, "wb")) == NULL) {
    perror(oname);
    if (fclose(istream) == EOF)
      perror(iname);
    exit(EXIT_FAILURE);
  }

  do {
    ch = fgetc(istream);
    if (ch == 0x0D) {
      if ((next = fgetc(istream)) == 0x0A)
        newline = '\n';
      else if (next == EOF)
        ungetc(next, istream);
    }
    if (!newline && ch != EOF)
      buffer[i++] = (unsigned char)ch;

    if (i == BUFFER_MAX || newline || (ch == EOF && i > 0)) {
      if (fwrite(buffer, sizeof(buffer[0]), i, ostream) < i) {
        perror(oname);
        errno = 0;
        rc = EXIT_FAILURE;
        break;
      }
      i = 0;
    }

    if (newline) {
      if (fputc(newline, ostream) == EOF) {
        perror(oname);
        errno = 0;
        rc = EXIT_FAILURE;
        break;
      }
      newline = '\0';
    }
  } while (ch != EOF);

  if (ferror(istream)) {
    perror(iname);
    rc = EXIT_FAILURE;
  }

  if (fclose(istream) == EOF) {
    perror(iname);
    rc = EXIT_FAILURE;
  }

  if (fclose(ostream) == EOF) {
    perror(oname);
    rc = EXIT_FAILURE;
  }

  return rc;
}
