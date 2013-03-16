#include "test_runner.h"

typedef enum {NORTH, SOUTH, EAST, WEST} direction;
typedef struct {int x; int y; } point;

point move(point p, direction d)
{
  switch(d) {
  case NORTH:
    p.y++;
    break;
  case SOUTH:
    p.y--;
    break;
  case EAST:
    p.x--;
    break;
  case WEST:
    p.x++;
    break;
  }
  return p;
}

point center(void) { return (point) {0, 0}; }

int move_south_test(void)
{
  point moved = move(center(), SOUTH);
  _assert(moved.x == 0);
  _assert(moved.y == -1);

  return 0;
}
int move_east_test(void)
{
  point moved = move(center(), EAST);
  _assert(moved.x == -1);
  _assert(moved.y == 0);
  return 0;
}
int move_west_test(void)
{
  point moved = move(center(), WEST);
  _assert(moved.x == 1);
  _assert(moved.y == 0);
  return 0;
}
int move_north_test(void)
{
  point moved = move(center(), NORTH);
  _assert(moved.x == 0);
  _assert(moved.y == 1);
  return 0;
}
int move_northwest_test(void)
{
  point moved = move(center(), NORTH);
  moved = move(moved, WEST);
  _assert(moved.x == 1);
  _assert(moved.y == 1);
  return 0;
}
int all_tests(void)
{
  _run(move_south_test);
  _run(move_east_test);
  _run(move_west_test);
  _run(move_north_test);
  _run(move_northwest_test);
  return 0;
}
