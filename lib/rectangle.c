#include "rectangle.h"

int area(rectangle r)
{
  return height(r) * width(r);
}
point center(rectangle r)
{
  return (point) {width(r) / 2, height(r) / 2};
}
rectangle move(rectangle r, int x, int y)
{
  r.upper_left.x += x;
  r.lower_right.x += x;
  r.upper_left.y += y;
  r.lower_right.y += y;

  return r;
}
bool is_inside(rectangle r, point p)
{
  if (p.x >= r.upper_left.x &&
      p.x <= r.lower_right.x &&
      p.y >= r.upper_left.y &&
      p.y <= r.lower_right.y) {
    return true;
  }

  return false;
}
int height(rectangle r)
{
  return r.lower_right.y - r.upper_left.y;
}
int width(rectangle r)
{
  return r.lower_right.x - r.upper_left.x;
}
