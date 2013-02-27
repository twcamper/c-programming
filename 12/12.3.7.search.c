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

int main(void)
{
  int a[] = {123,456, 99, 0, -12, 77};

  printf("found 99?: %d\n", search(a, 6, 99));
  printf("found 199?: %d\n", search(a, 6, 199));
  return 0;
}
