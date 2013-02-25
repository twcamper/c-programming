#include <stdio.h>
#include <stdlib.h>

void split_date(int day_of_year, int year, int *month, int *day)
{
  int eom[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int previous_month_end, current_month_end;

  /*leap year?*/
  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    eom[2] = 29;

  previous_month_end = 0;
  *month = 1;
  current_month_end = eom[*month];
  /*
   * Find the closest month end by looping
   * until we are between the previous EOM and the EOM of our day_of_year
  */
  while (!(day_of_year > previous_month_end && day_of_year <= current_month_end)) {
    previous_month_end = current_month_end;
    current_month_end += eom[++*month];
  }
  *day = day_of_year - previous_month_end;
}

int main(int argc, char *argv[])
{
  int dd, yyyy, month, day;

  if (argc != 3) {
    fprintf(stderr, "Usage: $ %s <dd> <yyyy>\n", argv[0]);
    return 1;
  }

  dd = atoi(argv[1]);
  yyyy = atoi(argv[2]);
  split_date(dd, yyyy, &month, &day);

  printf("%d, %d: %.2d/%.2d\n", yyyy, dd, month, day);

  return 0;
}
