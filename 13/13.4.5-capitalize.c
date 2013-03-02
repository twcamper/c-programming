#include <stdio.h>
#include <ctype.h>

void capitalize(char *str);

int main(void)
{
  char s[] = "what is wrong with you, lucille?";

  printf("before:\v%s\n", s);
  capitalize(s);
  printf("after:\v%s\n", s);

  return 0;
}

void capitalize(char *str)
{
  char *ch_ptr;
  for (ch_ptr = str; *ch_ptr != '\0'; ch_ptr++)
    *ch_ptr = toupper(*ch_ptr);
}
