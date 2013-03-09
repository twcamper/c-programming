#include <stdio.h>

#define CUBE(x) ((x) * (x) * (x))
#define NMOD_4(n) ((int)(n) % 4)
#define XY(x,y) ( (x)*(y) < 100 ? (x)*(y) : 0 )

int main(void)
{
  int y = 2;

  printf("%.3f, %d\n", CUBE(1.2), CUBE(y + 3));

  printf("%d, %d\n", NMOD_4(7.9), NMOD_4(17));

  printf("%.3f\n", XY(14.0,.3f));

  return 0;
}
