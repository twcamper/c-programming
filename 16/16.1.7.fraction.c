#include <stdio.h>
#include "error.h"

typedef struct { int numerator, denominator; } fraction;

int gcd(int a, int b);
fraction reduce(fraction );
void print_fraction(char *, fraction);
fraction add(fraction, fraction);

int main(int argc, char *argv[])
{
  if (argc < 3)
    invocation_error(argv[0], "int int  (i.e., numerator and denominator)");

  fraction f1 = { atoi(argv[1]), atoi(argv[2])};
  fraction f2, result;
  print_fraction("F1", f1);

  if (argc == 5)  {
    f2.numerator = atoi(argv[3]);
    f2.denominator = atoi(argv[4]);
    print_fraction("F2", f2);
  }
  printf("F1 GCD: %d\n", gcd(f1.numerator, f1.denominator));
  print_fraction("F1 Reduced", reduce(f1));
  result = add(f1, f2);
  print_fraction("f1 + f2 =", result);

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

fraction add(fraction f1, fraction f2)
{
  print_fraction("adding", f1);
  print_fraction("adding", f2);
  fraction f = {f1.numerator + f2.numerator, gcd(f1.denominator, f2.denominator) };
  print_fraction("adding", f);
  return reduce(f);
}
void print_fraction(char *header, fraction f)
{
  printf("%s %d/%d\n", header, f.numerator, f.denominator);
}
