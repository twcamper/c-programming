#include <stdio.h>

int check(int x, int y, int n)
{
  return x >= 0 && x < n && y >= 0 && y < n;
}

int gcd(int m, int n)
{
  int r;
  while (n != 0) {
    r = m % n;
    m = n;
    n = r;
  }
  return m;
}

int day_of_year(int m, int d, int yyyy)
{
  int month_lengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int i, days = 0;

  /*leap year?*/
  if ((yyyy % 4 == 0 && yyyy % 100 != 0) || yyyy % 400 == 0)
    month_lengths[1] = 29;

  /*accumulate all the days in each preceding month*/
  for (i = 0; i < m - 1; i++)
    days += month_lengths[i];

  return days + d;
}

int main(void)
{
  int int1, int2, int3;

  printf("Exercise 9.2 - enter x, y, and n: ");
  scanf("%d %d %d", &int1, &int2, &int3);
  printf("Are x and y between 0 and n? %d\n", check(int1, int2, int3));

  printf("Exercise 9.3 - enter m and n: ");
  scanf("%d %d", &int1, &int2);
  printf("Greatest Common Divisor: %d\n", gcd(int1, int2));

  printf("Exercise 9.4 - enter a date as mm/dd/yyyy: ");
  scanf("%d/%d/%d", &int1, &int2, &int3);
  printf("Day of Year: %d\n", day_of_year(int1, int2, int3));

  return 0;
}
