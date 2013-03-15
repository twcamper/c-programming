#include <assert.h>
#include "rectangle.h"

int main(void)
{
  rectangle R;

  R.upper_left  = (point) {0,0};
  R.lower_right =  (point) {0,0};
  assert(R.upper_left.x == 0);
  assert(R.upper_left.y == 0);
  assert(R.lower_right.x == 0);
  assert(R.lower_right.y == 0);

  assert(area(R) == 0);

  R.upper_left  = (point) {1,1};
  R.lower_right =  (point) {10,10};
  assert(R.upper_left.x == 1);
  assert(R.upper_left.y == 1);
  assert(R.lower_right.x == 10);
  assert(R.lower_right.y == 10);

  assert(height(R) == 9);
  assert(width(R) == 9);
  assert(area(R) == 81);

  point c = center(R);
  assert(c.x == 4);
  assert(c.y == 4);
  assert(is_inside(R, c) == true);

  int on_left = 1;
  int on_right = 10;
  int on_top = 1;
  int on_bottom = 10;
  int to_left = 0;
  int to_right = 11;
  int above  = 0;
  int below  = 11;

  assert(is_inside(R, (point) {on_left,on_bottom}) == true);
  assert(is_inside(R, (point) {on_left,on_top}) == true);
  assert(is_inside(R, (point) {on_right,on_top}) == true);
  assert(is_inside(R, (point) {on_right,on_bottom}) == true);

  assert(is_inside(R, (point) {to_left,below}) == false);
  assert(is_inside(R, (point) {to_left,above}) == false);
  assert(is_inside(R, (point) {to_right,above}) == false);
  assert(is_inside(R, (point) {to_right,below}) == false);

  assert(is_inside(R, (point) {on_left,below}) == false);
  assert(is_inside(R, (point) {on_left,above}) == false);
  assert(is_inside(R, (point) {on_right,above}) == false);
  assert(is_inside(R, (point) {on_right,below}) == false);

  assert(is_inside(R, (point) {to_left,on_bottom}) == false);
  assert(is_inside(R, (point) {to_right,on_bottom}) == false);
  assert(is_inside(R, (point) {to_left,on_top}) == false);
  assert(is_inside(R, (point) {to_right,on_top}) == false);

  rectangle moved = move(R, -3, 20);
  assert(area(moved) == 81);
  assert(moved.upper_left.x == -2);
  assert(moved.upper_left.y == 21);
  assert(moved.lower_right.x == 7);
  assert(moved.lower_right.y == 30);

  return 0;
}
