#include <stdio.h>
#include <time.h>
#include "time_helper.h"

typedef struct
{
  int month, day, year;
} date;
int day_of_year(date d)
{
  int eom[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int i, days = 0;

  /*leap year?*/
  if ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0)
    eom[2] = 29;

  /*accumulate all the days in each preceding month*/
  for (i = 0; i < d.month; i++)
    days += eom[i];

  return days + d.day;
}
void print_date(date d)
{
  printf("%d/%d/%d\n", d.month, d.day, d.year);
}
int compare_dates(date d1, date d2)
{
  if (d1.year < d2.year)
    return -1;
  else if (d1.year > d2.year)
    return 1;
  else {
    int day1 = day_of_year(d1);
    int day2 = day_of_year(d2);
    if (day1 < day2)
      return -1;
    if (day1 > day2)
      return 1;
  }
  return 0;
}

date random_date()
{
  struct tm *t = random_tm();
  return (date) {t->tm_mon + 1, t->tm_mday, t->tm_year + 1900};
}
int main()
{
  srand((unsigned) time(NULL));

  date d1 = random_date();
  date d2 = random_date();
  print_date(d1);
  print_date(d2);
  printf("%d\n", compare_dates(d1, d2));
  d1.year = d2.year;
  print_date(d1);
  print_date(d2);
  printf("%d\n", compare_dates(d1, d2));

  return 0;
}
