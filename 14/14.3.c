#include <stdio.h>
#include <string.h>


#define CUBE(x) ((x) * (x) * (x))
#define NMOD_4(n) ((int)(n) % 4)
#define XY(x,y) ( (x)*(y) < 100 ? (x)*(y) : 0 )
#define NELEMS(a) ((int) (sizeof(a) / sizeof(a[0])))
#define AVG(x,y) ((x)+(y)/2)
#define AREA(x,y) ((x)*(y))
#define TOUPPER(c) ('a' <= (c) && (c) <= 'z' ? (c)-'a'+'A':(c))
#define DISP(f,x)  printf(#f "(%g) = %g\n", (x), f(x))
#define NEWLINE printf("\n")

double square(double x)
{
  return x * x;
}
void test_disp(void)
{
  NEWLINE;
  DISP(square, 3.0);

  NEWLINE;
}
void test_toupper(void)
{
  puts("");
  char s[5];
  strcpy(s, "abcd");
  int i = 0;
  putchar(TOUPPER(s[++i]));

  puts("");

  strcpy(s, "0123");
  i = 0;
  putchar(TOUPPER(s[++i]));

  puts("");
}
void test_nelms_macro(void)
{
   int    ai[1234] = {0};
   float  af[2234] = {0.0};
   double ad[3234] = {0.0};
   char   ac[4234] = {'\0'};

   printf("\nTesting Arrays\n");
   printf("%d int\n", NELEMS(ai));
   printf("%d float\n", NELEMS(af));
   printf("%d double\n", NELEMS(ad));
   printf("%d char\n", NELEMS(ac));
}

int main(void)
{
  int y = 2;

  printf("%.3f, %d\n", CUBE(1.2), CUBE(y + 3));

  printf("%d, %d\n", NMOD_4(7.9), NMOD_4(17));

  printf("%.3f\n", XY(14.0,.3f));

  test_nelms_macro();

  test_toupper();

  test_disp();

  return 0;
}
