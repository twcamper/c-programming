#include <stdio.h>

int max(int a[], int n);
int avg(int a[], int n);
int positive_count(int a[], int n);

int main(void)
{
  int array[] = {12, 31, 0, 15, 2, 99, 1024, 8, 512, -299};

  int size = ((int) (sizeof(array) / sizeof(array[0])));
  printf("Max: %d\n", max(array, size));
  printf("Average: %d\n", avg(array, size));
  printf("Positive count: %d of %d\n", positive_count(array, size), size);
  return 0;
}

int max(int a[], int n)
{
  int i, m = a[0];
  for (i = 1; i < n; i++) {
    if (a[i] > m)
      m = a[i];
  }
  return m;
}
int avg(int a[], int n)
{
  int i, sum = 0;
  for (i = 0; i < n; i++)
    sum += a[i];

  return sum / n;
}
int positive_count(int a[], int n)
{
  int i, count = 0;
  for (i = 0; i < n; i++) {
    if (a[i] > 0)
      count++;
  }

  return count;
}
