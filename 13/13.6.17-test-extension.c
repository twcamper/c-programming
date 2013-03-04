#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


bool test_extension(const char *filename, const char *ext)
{
  int f_size = strlen(filename);
  int e_size = strlen(ext);
  if (e_size >= f_size)
    return false;

  /* where the extension would start in the file name */
  const char *p = (filename + f_size) - e_size;
  while (*p)
    /* "*p++":  get the value, then increment the pointer */
    if (toupper(*p++) != toupper(*ext++))
      return false;

  return true;
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Usage: %s file_name ext\n", argv[0]);
    return 1;
  }

  printf("%d\n", test_extension(argv[1], argv[2]));

  return 0;
}
