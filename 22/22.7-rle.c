#include <stdio.h>
#include <string.h>
#include "error.h"

/* Run Length Encoding */
#define EXT ".rle"
#define EXT_LEN 4
#define BUFFER_SIZE BUFSIZ
static void encode(FILE *in, FILE *out)
{
  /* fread proved unreliable with int elements */
  char inbuffer[BUFFER_SIZE] = {0};
  char outbuffer[BUFFER_SIZE] = {0};
  size_t i;
  size_t n_read = 0, n_written = 0;

  for (;;) {
    if ((n_read = fread(inbuffer, sizeof(inbuffer[0]), BUFFER_SIZE, in)) < BUFFER_SIZE) {
      if (ferror(in)) {
        print_error(errno, __FILE__, "fread(in)");
        return;
      }
      if (feof(in) && n_read == 0)
        break;
    }

    for (i = 0; i < n_read; i++)
      outbuffer[i] = inbuffer[i];

    if ((n_written = fwrite(outbuffer, sizeof(outbuffer[0]), n_read, out)) < n_read) {
      if (ferror(out)) {
        print_error(errno, __FILE__, "fwrite(out)");
        return;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    invocation_error(argv[0], "[file]");

  FILE *istream;
  if ((istream = fopen(argv[1], "rb")) == NULL)
    exit_error(errno, argv[0], argv[1]);

  /*
   * Build output file name
   */
  char outfile_name[strlen(argv[1]) + EXT_LEN + 1];

  strcpy(outfile_name, argv[1]);
  strncat(outfile_name, EXT, EXT_LEN + 1);

  FILE *ostream;
  if ((ostream = fopen(outfile_name, "wb")) == NULL) {
    print_error(errno, argv[0], outfile_name);
    if (fclose(istream) == EOF)
      exit_error(errno, argv[0], argv[1]);
    exit(EXIT_FAILURE);
  }

  /*
   * Process
   */
  encode(istream, ostream);

  /*
   * Close Files
   */
  if (fclose(istream) == EOF)
    print_error(errno, argv[0], argv[1]);

  if (fclose(ostream) == EOF)
    exit_error(errno, argv[0], outfile_name);

  return 0;
}
