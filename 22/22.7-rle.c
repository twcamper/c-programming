#include <stdio.h>
#include <string.h>
#include "run-length-encoding.h"

int main(int argc, char *argv[])
{
  char *program = argv[0];
  if (argc != 2)
    invocation_error(program, "[file]");

  char *iname  = argv[1];
  FILE *istream;
  if ((istream = fopen(iname, "rb")) == NULL)
    exit_error(program, iname);

  char *oname = build_output_file_name(iname);
  FILE *ostream;
  if ((ostream = fopen(oname, "wb")) == NULL) {
    print_error(program, oname);
    free(oname);
    if (fclose(istream) == EOF)
      exit_error(program, iname);
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
    print_error(program, iname);

  if (fclose(ostream) == EOF)
    exit_error(program, oname);

  return 0;
}
