#include <stdio.h>
#include <string.h>

void get_extension(char *file_name, char *extension)
{

  char *f_ptr = file_name + strlen(file_name);

  extension[0] = '\0';
  while  (f_ptr >= file_name) {
   if (*f_ptr == '.') {
     strcpy(extension, ++f_ptr);
     break;
   } else
    f_ptr--;
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
