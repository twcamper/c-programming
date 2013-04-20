#include "run-length-encoding.h"
#define BUFFER_SIZE BUFSIZ
#define MAX_RUN UCHAR_MAX
void encode_rle(FILE *in, FILE *out)
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
      if (previous == inbuffer[i] && occurrences < MAX_RUN) {
        /*
         * keep counting as long as the byte value doesn't change
         * and we have room in the 'occurrences' variable
         */
        occurrences++;
      } else {
        outbuffer[n_encoded++] = occurrences;
        outbuffer[n_encoded++] = previous;
        occurrences = 1;
      }
      previous = inbuffer[i];
    }

    /* store data on the last run, which the loop can't handle */
    if (i) {
      outbuffer[n_encoded++] = occurrences;
      outbuffer[n_encoded++] = previous;
    }

    n_written = fwrite(outbuffer, sizeof(outbuffer[0]), n_encoded, out);
    if (n_written < n_encoded || ferror(out)) {
      print_error(errno, __FILE__, "fwrite(out)");
      return;
    }
  }
}

