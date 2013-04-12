#include <stdio.h>

#define MK_COLOR(r,g,b) ((unsigned long) (b) << 16 | (g) << 8 | (r))
#define GET_RED(rgb) ((unsigned int) (rgb) & 0x00FF)
#define GET_BLUE(rgb) ((unsigned int) ((rgb) >> 8) & 0x00FF)
#define GET_GREEN(rgb) ((unsigned int) ((rgb) >> 16) & 0x00FF)

void ex_1(void)
{
  unsigned short int i, j, k = 0;

  i = 8;
  j = 9;
  printf("ex 1a) Precedence! %d\n", i >> 1 + j >> 1);
  printf("%d\n", (i >> 1) + (j >> 1));

  i = 1;
  printf("ex 1b) %d\n", i & ~i);

  i = 2; j = 1; k = 0;
  printf("ex 1c) %d\n", ~i & j ^ k);
  printf("   ==) %d\n", (((~i) & j) ^ k));

  i = 7; j = 1; k = 9;
  printf("ex 1d) %d\n", i ^ j & k);
  printf("   ==) %d\n", i ^ (j & k));

}

unsigned short int toggle(unsigned short int value, unsigned short int bit)
{
  /* unsigned short int mask = 0 | (1 << bit); */
  /* printf("\tvalue: %d, mask: 0x%.4X\n", value, mask); */
  /* if (value & mask) */
    /* value &= ~mask; */
  /* else */
    /* value |= 1 << bit; */

  return value ^= 1 << bit;
}
void ex_2(void)
{
  printf("\nEx. 2\n");
  unsigned short int i = 9;
  printf("%d\n", (i = toggle(i, 4)));
  printf("%d\n", (i = toggle(i, 4)));

  printf("%d\n", (i = toggle(i, 7)));
  printf("%d\n", (i = toggle(i, 7)));

}
void ex_4(void)
{
  printf("%.4X\n", (unsigned int)MK_COLOR(255,32,96));
}
void ex_5(void)
{
  unsigned long rgb = MK_COLOR(25,32,96);
  printf("Red: %.4X\n", GET_RED(rgb));
  printf("Blue: %.4X\n", GET_BLUE(rgb));
  printf("Green: %.4X\n", GET_GREEN(rgb));
}
int main(void)
{
  ex_1();
  ex_2();
  ex_4();
  ex_5();
  return 0;
}
