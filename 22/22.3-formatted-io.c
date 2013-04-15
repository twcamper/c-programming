#include <stdio.h>

void ex_4(void)
{
  char *format = "%#012.5g\n";
  puts("00000083.736");
  printf(format, 83.7361);
  puts("000000029748");
  printf(format, 29748.6607);
  puts("000000029748");
  printf(format, 105493234.0);
}
void ex_5(void)
{
  printf("%.4d\n", 12);
  printf("%04d\n", 12);
  printf("%.4d\n", 12345);
  printf("%04d\n", 12345);
}

void wp(int i)
{
  printf((i == 1) ? "%d widget\n" : "%d widgets\n", i);
}

void ex_6(void)
{
  wp(1);
  wp(2);
  wp(0);
}

void ex_7(void)
{
  char *a = "10 20 30\n";
  char *b = "1.0 2.0 3.0\n";
  char *c = "0.1 0.2 0.3\n";
  char *d = ".1 .2 .3\n";
  char *fmt = "%d%f%d";
  char *out = "i: %d, f: %f, j: %d, n: %d\n";
  int i = 0, j = 0, n = 0;
  float f = 0.0;

  n = sscanf(a, fmt, &i, &f, &j);
  printf(out, i, f, j, n);

  n = sscanf(b, fmt, &i, &f, &j);
  printf(out, i, f, j, n);

  n = sscanf(c, fmt, &i, &f, &j);
  printf(out, i, f, j, n);

  n = sscanf(d, fmt, &i, &f, &j);
  printf(out, i, f, j, n);

}
int main(void)
{
  ex_4();
  ex_5();
  ex_6();
  ex_7();
  return 0;
}
