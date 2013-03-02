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
  for (int i = 0; str[i] != '\0'; i++)
    str[i] = toupper(str[i]);
}
