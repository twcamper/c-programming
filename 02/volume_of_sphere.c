#include <stdio.h>
# define M_PI   3.14159265358979323846  /* pi */

int main(void)
{
  float volume, radius;

  printf("Enter a radius: ");
  scanf("%f", &radius);

  volume = 4.0f/3.0f * M_PI * radius;

  printf("Volume of Sphere (radius %.2f): %.10f\n", radius, volume);
  return 0;
}
