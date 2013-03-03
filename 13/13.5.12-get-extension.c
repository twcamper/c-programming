#include <stdio.h>
#include <string.h>

void get_extension(char *file_name, char *extension)
{

  int i = strlen(file_name) - 1;

  extension[0] = '\0';

  while  (i >= 0) {
    if (file_name[i] == '.') {
      strcpy(extension, &file_name[++i]);
      break;
    } else
      i--;
  }

}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s file_name.ext\n", argv[0]);
    return 1;
  }
  char ext[16];
  get_extension(argv[1], ext);
  printf("File Extension: '%s'\n", ext);

  return 0;
}
