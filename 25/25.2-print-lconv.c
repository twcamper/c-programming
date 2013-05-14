#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <locale.h>
#include <monetary.h>

#define CURRENCY_MAX 16
int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "%s locale\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *l = setlocale(LC_ALL, argv[1]);
  if (!l) {
    fprintf(stderr, "setlocale() failed for %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  puts(l);

  struct lconv *locale = localeconv();
  printf("decimal_point = \"%s\"\n", locale->decimal_point);
  printf("thousands_sep = \"%s\"\n", locale->thousands_sep);
  printf("grouping = \"%s\" : %d\n", locale->grouping, atoi(locale->grouping));
  printf("mon_decimal_point = \"%s\"\n", locale->mon_decimal_point);
  printf("mon_thousands_sep = \"%s\"\n", locale->mon_thousands_sep);
  printf("mon_grouping = \"%s\" : %d\n", locale->mon_grouping, atoi(locale->mon_grouping));
  printf("positive_sign = \"%s\"\n", locale->positive_sign);
  printf("negative_sign = \"%s\"\n", locale->negative_sign);
  printf("currency_symbol = \"%s\"\n", locale->currency_symbol);
  printf("frac_digits = %d\n", locale->frac_digits);
  puts("etc.");

  return 0;
}
