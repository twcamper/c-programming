#include <stdio.h>
#include <string.h>
#include "run-length-encoding.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
    invocation_error(argv[0], "[file]");
  char *program = argv[0];

  char *iname  = argv[1];
  FILE *istream;
  if ((istream = fopen(iname, "rb")) == NULL)
    exit_error(errno, program, iname);

  char *oname = build_output_file_name(iname);
  FILE *ostream;
  if ((ostream = fopen(oname, "wb")) == NULL) {
    print_error(errno, program, oname);
    if (fclose(istream) == EOF)
      exit_error(errno, program, iname);
    exit(EXIT_FAILURE);
  }

  /*
   * Process
   */
  if (is_rle_file(oname))
    encode_rle(istream, ostream);
  else
    decode_rle(istream, ostream);

  /*
   * Clean up
   */
  free(oname);

  if (fclose(istream) == EOF)
    print_error(errno, program, iname);

  if (fclose(ostream) == EOF)
    exit_error(errno, program, oname);

  return 0;
}
