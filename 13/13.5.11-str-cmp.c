#include <stdio.h>

int str_cmp(char *s, char *t);

void print_comparison(char *a, char *b)
{
  int result = str_cmp(a, b);
  printf("%s == %s? %d:(%d)\n", a, b, (result == 0), result);
}
int main(void)
{
  char *a = "abc", *b = "ABC", *c = "0123", *d = "abcd";

  print_comparison(a, b);
  print_comparison(a, "abc");
  print_comparison(b, a);
  print_comparison(a, c);
  print_comparison(a, d);
  print_comparison(d, c);
  print_comparison(c, d);
  return 0;
}

int str_cmp(char *s, char *t)
{
  for (;*s == *t; s++, t++)
    if (!*s)
      return 0;

  return *s - *t;
}
