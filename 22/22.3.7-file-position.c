#include <stdio.h>

#define RECORD_SIZE 64

int fseek_calls(void)
{
  FILE *fp = fopen("dummy", "rb");
  if (!fp)
    return -1;
  int n = 52;
  /* a) move to the beginning of record n */
  fseek(fp, RECORD_SIZE * n, SEEK_SET);

  /* b) move to the beginning of the last record in the file */
  fseek(fp, -RECORD_SIZE, SEEK_END);

  /* c) move forward one record */
  fseek(fp, RECORD_SIZE, SEEK_CUR);

  /* d) move backward 2 records */
  fseek(fp, -(2 * RECORD_SIZE), SEEK_CUR);

  return 0;
}

int main(void)
{

  return 0;
}
