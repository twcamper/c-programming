#include <stdio.h>

int i = 0;

int main(void)
{
  printf("Global %d\n", i);
  int i = 1;
  printf("Main %d\n", i);

  {
    printf("First Block %d\n", i);
    int i = 2;
    printf("First Block %d\n", i);

    {
      printf("Second Block %d\n", i);
      int i = 3;
      printf("Second Block %d\n", i);
      {
        printf("Innermost Block %d\n", i);
        int i = 4;
        printf("Innermost Block %d\n", i);
      }
    }
  }

  printf("Main %d\n", i);
  return 0;
}
