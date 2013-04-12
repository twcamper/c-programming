#include <stdio.h>

int main(void)
{
  char *filename = "foo.txt";

  FILE *fp;

  if ((fp = fopen(filename, "r"))) {
    printf("%s can be read.\n", filename);
    fclose(fp);  /* close was outside of the block, would have been called after failure on open */
  } else {
    printf("can't read jack shit.\n");
  }
  return 0;
}
