#include <stdio.h>

int main(void)
{
  int hours, minutes;
  char meridian[] = "AM";

  printf("Enter a 24-hour time: ");
  scanf("%d:%d", &hours, &minutes);

  if (hours >= 12) {
    meridian[0] = 'P';
    hours -= 12;
  }
  if (hours == 0)
    hours = 12;

  printf("Equivalent 12-hour time: %d:%.2d %s\n", hours, minutes, meridian);

  return 0;
}
