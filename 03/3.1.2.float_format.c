#include <stdio.h>

int main(void)
{
  printf("Exercise 3.1.1\n");
  printf("%6d, %4d\n", 86, 1040);
  printf("%12.5e\n", 30.253);
  printf("%.4f\n", 83.162);
  printf("%-6.2g\n", .0000009979);


  printf("\nExercise 3.1.2\n");

  float x = 12.9f;
  printf("|%-8.1e|%10.6e|%-8.3f|%6.0f|\n", x, x, x, x);


  return 0;
}
