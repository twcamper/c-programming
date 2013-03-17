#include "rectangle.h"
#include "test_runner.h"

rectangle nine_by_nine(void)
{
  return (rectangle) {(point){1,1}, (point) {10,10} };
}

int test_zeroes(void)
{
  rectangle R;

  R.upper_left  = (point) {0,0};
  R.lower_right =  (point) {0,0};
  _assert(R.upper_left.x == 0);
  _assert(R.upper_left.y == 0);
  _assert(R.lower_right.x == 0);
  _assert(R.lower_right.y == 0);

  _assert(area(R) == 0);
  point c = center(R);
  _assert(c.x == 0);
  _assert(c.y == 0);

  return 0;
}

int test_area(void)
{
  rectangle R = nine_by_nine();
  _assert(R.upper_left.x == 1);
  _assert(R.upper_left.y == 1);
  _assert(R.lower_right.x == 10);
  _assert(R.lower_right.y == 10);

  _assert(height(R) == 9);
  _assert(width(R) == 9);
  _assert(area(R) == 81);

  return 0;
}

int test_center(void)
{
  rectangle R = nine_by_nine();
  point c = center(R);
  _assert(c.x == 4);
  _assert(c.y == 4);
  _assert(is_inside(R, c) == true);

  return 0;
}

int test_is_inside(void)
{
  int left     = 1;
  int right    = 10;
  int top      = 1;
  int bottom   = 10;
  int to_left  = left - 1;
  int to_right = right + 1;
  int above    = top - 1;
  int below    = bottom + 1;

  rectangle R = {(point){top,left}, (point){bottom,right} };
  _assert(is_inside(R, (point) {left,bottom}) == true);
  _assert(is_inside(R, (point) {left,top}) == true);
  _assert(is_inside(R, (point) {right,top}) == true);
  _assert(is_inside(R, (point) {right,bottom}) == true);

  _assert(is_inside(R, (point) {to_left,below}) == false);
  _assert(is_inside(R, (point) {to_left,above}) == false);
  _assert(is_inside(R, (point) {to_right,above}) == false);
  _assert(is_inside(R, (point) {to_right,below}) == false);

  _assert(is_inside(R, (point) {left,below}) == false);
  _assert(is_inside(R, (point) {left,above}) == false);
  _assert(is_inside(R, (point) {right,above}) == false);
  _assert(is_inside(R, (point) {right,below}) == false);

  _assert(is_inside(R, (point) {to_left,bottom}) == false);
  _assert(is_inside(R, (point) {to_right,bottom}) == false);
  _assert(is_inside(R, (point) {to_left,top}) == false);
  _assert(is_inside(R, (point) {to_right,top}) == false);
  return 0;
}

int test_move(void)
{
  rectangle R = nine_by_nine();
  rectangle moved = move(R, -3, 20);
  _assert(area(moved) == 81);
  _assert(moved.upper_left.x == -2);
  _assert(moved.upper_left.y == 21);
  _assert(moved.lower_right.x == 7);
  _assert(moved.lower_right.y == 30);

  return 0;
}

int test_move_copies(void)
{
  rectangle R = nine_by_nine();
  rectangle moved = move(R, -3, 20);

  _assert(R.upper_left.x == 1);
  _assert(R.upper_left.y == 1);
  _assert(R.lower_right.x == 10);
  _assert(R.lower_right.y == 10);
  _assert(&R != &moved);
  return 0;
}

int all_tests(void)
{
  _run(test_zeroes);
  _run(test_area);
  _run(test_center);
  _run(test_is_inside);
  _run(test_move);
  _run(test_move_copies);
  return 0;
}
