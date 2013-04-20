#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "error.h"

/* Run Length Encoding */
#define EXT ".rle"
#define EXT_LEN 4
#define BUFFER_SIZE BUFSIZ
static void encode(FILE *in, FILE *out)
{
  /* fread proved unreliable with int elements */
  unsigned char inbuffer[BUFFER_SIZE] = {0};
  /* encoded output can be up to 2x the input */
  unsigned char outbuffer[BUFFER_SIZE * 2] = {0};
  size_t i, n_read = 0, n_written = 0;
  unsigned char previous, occurrences;
  unsigned int n_encoded;

  for (;;) {
    if ((n_read = fread(inbuffer, sizeof(inbuffer[0]), BUFFER_SIZE, in)) < BUFFER_SIZE) {
      if (ferror(in)) {
        print_error(errno, __FILE__, "fread(in)");
        return;
      }
      if (feof(in) && n_read == 0)
        break;
    }

    previous = inbuffer[0];
    for (n_encoded = 0, i = 0; i < n_read; i++) {
      if (previous == inbuffer[i]) {
        if (occurrences == 255) {
          fprintf(stderr, "Consecutive character run count exceeds 255 byte max.\n");
          exit(EXIT_FAILURE);
        }
        occurrences++;
      } else {
        outbuffer[n_encoded++] = occurrences;
        outbuffer[n_encoded++] = previous;
        occurrences = 1;
      }
      previous = inbuffer[i];
    }

    n_written = fwrite(outbuffer, sizeof(outbuffer[0]), n_encoded, out);
    if (n_written < n_encoded || ferror(out)) {
      print_error(errno, __FILE__, "fwrite(out)");
      return;
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
