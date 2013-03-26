#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int test_1(void)
{
  char *s;
  int i;

  assert(sizeof(char) == 1);

  s = malloc(10);
  assert(s != NULL);

  s[10] = 'A';
  assert(s[10] == 'A');

  /* Threshhold on my machine: note, binary MB, 2**20, == 1048576 */
  i = 1048447;  /* works */
  i = 1048448;  /* segfualts */

  i = 1000000;
  s[i] = 'A';
  assert(s[i] == 'A');

  free(s);

  return 0;
}

int test_2(void)
{
  char *s;
  int i = 0;

  s = malloc(10);
  assert(s != NULL);

  for (;i < 100000; i++)
    strcat(s, "0123456789");

  puts(s);

  free(s);

  return 0;
}

int main(void)
{
  assert(test_1() == 0);
  assert(test_2() == 0);

  return 0;
}
