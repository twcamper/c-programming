#include <stdio.h>
#include <string.h>
#include "error.h"

/* Run Length Encoding */
#define EXT ".rle"
#define EXT_LEN 4

static void encode(FILE *in, FILE *out)
{

}

int main(int argc, char *argv[])
{
  if (argc != 2)
    invocation_error(argv[0], "[file]");

  FILE *infile;
  if ((infile = fopen(argv[1], "rb")) == NULL)
    exit_error(errno, argv[0], argv[1]);

  /*
   * Build output file name
   */
  char outfile_name[strlen(argv[1]) + EXT_LEN + 1];

  strcpy(outfile_name, argv[1]);
  strncat(outfile_name, EXT, EXT_LEN + 1);

  FILE *outfile;
  if ((outfile = fopen(outfile_name, "wb")) == NULL)
    exit_error(errno, argv[0], outfile_name);

  /*
   * Process
   */
  encode(infile, outfile);

  /*
   * Close Files
   */
  if (fclose(infile) == EOF)
    exit_error(errno, argv[0], argv[1]);

  if (fclose(outfile) == EOF)
    exit_error(errno, argv[0], outfile_name);

  return 0;
}
