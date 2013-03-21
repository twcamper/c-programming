#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *create_array(int n, int initial_value)
{
  int *a;
  a = malloc(n * sizeof(int));
  if (!a)
    return NULL;

  for (int i = 0; i < n; i++)
    a[i] = initial_value;

  return a;
}
#define SIZE 923
int main(void)
{
  int *A = create_array(SIZE, INT_MAX);

  for (int i = 0; i < SIZE; i++)
    printf("%d:%d\n", i, A[i]);

  puts("");
  return 0;
}
