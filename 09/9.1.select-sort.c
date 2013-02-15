#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RANGE 1024

void select_sort(int a[], int n);
void print_array(int a[], int n);

int main(int argc, char *argv[])
{
  int size = atoi(argv[1]);
  int i, sort_me[size];

  /*
   * Populate a test array with
   * a random series of integers
   */
  srand((unsigned) time(NULL));
  for (i = 0; i < size; i++)  {
    sort_me[i] = rand() % RANGE;
  }

  print_array(sort_me, size);
  select_sort(sort_me, size);
  printf("\n");
  print_array(sort_me, size);

  return 0;
}

void select_sort(int a[], int n)
{
  int i, index_of_max, max_value;

  if (n > 0) {
    /*
     * Find max value
     */
    max_value = a[0];
    index_of_max = 0;
    for (i = 1; i < n; i++) {
      if (a[i] > max_value) {
        max_value = a[i];
        index_of_max = i;
      }
    }

    /*
     * Move max to end
     *
     * First, shift everything to the left,
     * leaving the last element ( n - 1 ) open
     */
    for (i = index_of_max + 1; i < n; i++) {
      a[i - 1] = a[i];
    }
    a[n - 1] = max_value;

    /*
     * Next, sort the remainder of the array
     * (everything before the max val we just moved to the end)
     */
    select_sort(a, n - 1);
  }
}

void print_array(int a[], int n)
{
  int i;
  for (i = 0; i < n; i++)  {
    /*print the newline first, otherwise the first row is an odd length*/
    if (i > 0 && i % 12 == 0)
      printf("\n");
    printf("%d\t", a[i]);
    }

  printf("\n");
}
