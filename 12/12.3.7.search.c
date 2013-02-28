#include <stdbool.h>
#include <stdio.h>

bool search(const int a[], int n, int key)
{
  const int *pa;
  for (pa = a; pa < a + n; pa++)
    if (*pa == key)
      return true;

  return false;
}

bool search_temps(int t)
{
  int temperatures[7][24] = {
    {23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
    {23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
    {23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
    {23,23,23,23,23,23,23,23,23,23,32,23,23,23,23,23,23,23,23,23,23,23,23,23},
    {23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
    {23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
    {23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23}
  };

  int row;
  for (row = 0; row < 7; row++)
    if (search(temperatures[row], 24, t))
      return true;
  return false;
}
int main(void)
{
  int a[] = {123,456, 99, 0, -12, 77};

  printf("found 99?: %d\n", search(a, 6, 99));
  printf("found 199?: %d\n", search(a, 6, 199));

  printf("found 32?: %d\n", search_temps(32));
  printf("found 30?: %d\n", search_temps(30));
  return 0;
}
