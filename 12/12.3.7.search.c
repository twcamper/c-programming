#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DAYS 7
#define HOURS 24

int temperatures[DAYS][HOURS];

bool search(const int *a, int n, int key);
bool search_temps(int key);
void generate_temperatures(void);
void print_temperatures(int day);
int *find_largest(int *a, int n);

int main(void)
{
  int a[] = {123,456, 99, 0, -12, 77};

  printf("found 99?: %d\n", search(a, 6, 99));
  printf("found 199?: %d\n", search(a, 6, 199));

  generate_temperatures();
  *(temperatures[0] + (DAYS * HOURS / 2)) = 32;
  /* temperatures[DAYS/2][HOURS / 2] = 32; */

  printf("found 32?: %d\n", search_temps(32));
  printf("found 30?: %d\n", search_temps(30));
  
  for (int d = 0; d < DAYS; d++)  {
    printf("High for day %d: %2d -- ", d, *find_largest(temperatures[d], HOURS));
    print_temperatures(d);
  }

  return 0;
}
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

  int row;
  for (row = 0; row < DAYS; row++)
    if (search(temperatures[row], HOURS, t))
      return true;
  return false;
}
void generate_temperatures(void)
{
  srand((unsigned) time(NULL));

 for (int row = 0; row < DAYS; row++)
   for (int col = 0; col < HOURS; col++)
     temperatures[row][col] = rand() % 88;
}
void print_temperatures(int day)
{
  int *h_ptr;
  for (h_ptr = temperatures[day]; h_ptr < temperatures[day] + HOURS; h_ptr++)
    printf("%2d ", *h_ptr);
  printf("\n");
}
int *find_largest(int *a, int n)
{
  int *a_ptr, *max_ptr;
  max_ptr = a;
  for (a_ptr = a; a_ptr < a + n; a_ptr++) {
    if (*a_ptr > *max_ptr)
      max_ptr = a_ptr;
  }

  return max_ptr;
}
