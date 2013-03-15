#include <stdio.h>
#include <stdbool.h>

typedef struct {
  int red;
  int green;
  int blue;
} color;

color make_color(int red, int green, int blue);
int set_color(int c);
int get_red(color c);
bool colors_equal(color color1, color color2);
color brighter(color c);
color darker(color c);

int main(void)
{

  return 0;
}
color make_color(int red, int green, int blue)
{
  return (color) {set_color(red),
                  set_color(green),
                  set_color(blue)};
}
int get_red(color c)
{
  return c.red;
}
bool colors_equal(color color1, color color2)
{
  return (color1.red == color2.red &&
          color1.green == color2.green &&
          color1.blue == color2.blue);
}
int brighten(int c)
{
  if (c < 3) c = 3;
  c = (int) ( (float)c / 0.7f);
  return c > 255 ? 255 : c;
}
color brighter(color c)
{
  if (colors_equal(c, (color) {0,0,0}))
    return make_color(3,3,3);

  c.red   = brighten(c.red);
  c.green = brighten(c.green);
  c.blue  = brighten(c.blue);

  return c;
}
int darken(int c)
{
  return (int) ((float) c * 0.7f);
}
color darker(color c)
{
  c.red   = darken(c.red);
  c.green = darken(c.green);
  c.blue  = darken(c.blue);

  return c;
}
int set_color(int c)
{
  if (c < 0)   return 0;
  if (c > 255) return 255;
  return c;
}
