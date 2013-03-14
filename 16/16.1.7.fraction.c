#include <stdio.h>
#include "error.h"

typedef struct { int numerator, denominator; } fraction;

int gcd(int a, int b);
fraction reduce(fraction );
void print_fraction(char *, fraction);
void convert_terms(fraction *, fraction *);
fraction add(fraction, fraction);
fraction subtract(fraction, fraction);

int main(int argc, char *argv[])
{
  if (argc < 3)
    invocation_error(argv[0], "int int  (i.e., numerator and denominator)");

  fraction f1 = { atoi(argv[1]), atoi(argv[2])};
  fraction f2;
  print_fraction("F1", f1);

  if (argc == 5)  {
    f2.numerator = atoi(argv[3]);
    f2.denominator = atoi(argv[4]);
    print_fraction("F2", f2);
  }
  printf("F1 GCD: %d\n", gcd(f1.numerator, f1.denominator));
  print_fraction("F1 Reduced", reduce(f1));
  print_fraction("f1 + f2 =", add(f1, f2));
  print_fraction("f1 - f2 =", subtract(f1, f2));

  return 0;
}
int gcd(int a, int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);

}

fraction reduce(fraction f)
{
  int greatest_common_factor = gcd(f.numerator, f.denominator);
  return (fraction) {f.numerator / greatest_common_factor, f.denominator / greatest_common_factor};
}

/* express both fractions in terms of the lowest common denominator */
void convert_terms(fraction *f1, fraction *f2)
{
  fraction *with_greater = f1, *other = f2;
  int i, common_denominator;

  if (f2->denominator > with_greater->denominator) {
    with_greater = f2;
    other = f1;
  }

  i = 1;
  do {
    common_denominator = with_greater->denominator * i;
    i++;
  } while (common_denominator % other->denominator > 0);

  other->numerator         *= common_denominator / other->denominator;
  other->denominator        = common_denominator;
  with_greater->numerator  *= common_denominator / with_greater->denominator;
  with_greater->denominator = common_denominator;
}
fraction add(fraction f1, fraction f2)
{
  convert_terms(&f1, &f2);
  return reduce((fraction) {f1.numerator + f2.numerator, f1.denominator});
}
fraction subtract(fraction f1, fraction f2)
{
  convert_terms(&f1, &f2);
  return reduce((fraction) {f1.numerator - f2.numerator, f1.denominator});
}
void print_fraction(char *header, fraction f)
{
  printf("%s %d/%d\n", header, f.numerator, f.denominator);
}
