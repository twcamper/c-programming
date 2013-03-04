#include <stdio.h>

void remove_filename(char *url)
{
  char *p = NULL;
  while (*url) {
    if (*url == '/')
      p = url;
    url++;
  }

  /* if any slashes were found, this will point to the last of them */
  if (*p)
    *p  = '\0';
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <url>\n", argv[0]);
    return 1;
  }

  remove_filename(argv[1]);
  printf("%s\n", argv[1]);

  return 0;
}
