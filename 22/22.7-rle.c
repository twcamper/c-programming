#include <stdio.h>
#include <string.h>
#include "run-length-encoding.h"

/* Run Length Encoding */
#define EXT ".rle"
#define EXT_LEN 4

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
  encode_rle(istream, ostream);

  /*
   * Close Files
   */
  if (fclose(istream) == EOF)
    print_error(errno, argv[0], argv[1]);

  if (fclose(ostream) == EOF)
    exit_error(errno, argv[0], outfile_name);

  return 0;
}
