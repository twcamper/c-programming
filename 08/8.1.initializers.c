#include <stdio.h>
#include <stdbool.h>
#define FIB_MAX 40
int main(void)
{
  bool weekend[] = {true, false, false, false, false, false, true};
  bool wochenende[] = {[0] = true, [6] = true};
  int fibonacci_sequence[40] = {0, 1};

  int i;
  for (i = 2; i < FIB_MAX; i++) {
    fibonacci_sequence[i] = fibonacci_sequence[i-2] + fibonacci_sequence[i-1];
  }

  for (i = 0; i < FIB_MAX; i++) {
    printf("%2d)\t%3d\n", i + 1, fibonacci_sequence[i]);
  }

  return 0;
}
