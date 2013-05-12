#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#define BUFFER_MAX 1024

int convert_line_endings(int argc, char *argv[], int (*detect_newline)(FILE *, bool*), int (*write_newline)(FILE *))
{
  if (argc != 3) {
    fprintf(stderr, "Usage: %s [input file] [output file]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *iname  = argv[1];
  char *oname =  argv[2];;
  FILE *istream, *ostream;
  unsigned char buffer[BUFFER_MAX];
  int ch, rc = 0;
  size_t i = 0;
  bool newline = false;

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
    ch = detect_newline(istream, &newline);
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
      if (write_newline(ostream) == EOF) {
        perror(oname);
        errno = 0;
        rc = EXIT_FAILURE;
        break;
      }
      newline = false;
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
#if defined(DOS2UNIX)
static int detect_dos_newline(FILE *fp, bool *is_newline)
{
  int next = 0;
  int ch = fgetc(fp);
  if (ch == 0x0D) {
    if ((next = fgetc(fp)) == 0x0A)
      *is_newline = true;
    else if (next == EOF)
      ungetc(next, fp);
  }
  return ch;
}

static int write_unix_newline(FILE *fp)
{
  return fputc(0x0A, fp);
}
int main(int argc, char *argv[])
{
  return convert_line_endings(argc, argv, detect_dos_newline, write_unix_newline);
}
#elif defined(UNIX2DOS)
static int detect_unix_newline(FILE *fp, bool *is_newline)
{
  int ch;
  if ((ch = fgetc(fp)) == 0x0A)
    *is_newline = true;

  return ch;
}

static int write_dos_newline(FILE *fp)
{
  if (fputc(0x0D, fp) == EOF)
    return EOF;

  return fputc(0x0A, fp);
}

int main(int argc, char *argv[])
{
  return convert_line_endings(argc, argv, detect_unix_newline, write_dos_newline);
}
#endif
