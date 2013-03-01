#include <stdio.h>

int main(void)
{
  int i, j;
  char s[15];

  scanf("%d%s%d", &i, s, &j);

  printf("i: %d, j: %d, s: |%s|\n", i, j, s);
  return 0;
}
