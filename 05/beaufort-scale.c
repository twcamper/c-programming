#include <stdio.h>

int main(void)
{
  char *description;
  float wind_speed;

  printf("Enter wind speed (knots): ");
  scanf("%f", &wind_speed);

  if (wind_speed < 1.0f)
    description = "Calm";
  else if (wind_speed < 4.0f)
    description = "Light air";
  else if (wind_speed < 28.0f)
    description = "Breeze";
  else if (wind_speed < 48.0f)
    description = "Gale";
  else if (wind_speed < 63.01f)
    description = "Storm";
  else
    description = "Hurricane";

  printf("Wind Force: %s\n", description);

  return 0;
}
