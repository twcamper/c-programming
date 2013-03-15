#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdbool.h>

int area(rectangle r);
int center(rectangle r);
rectangle move(rectangle r, int x, int y);
bool is_inside(rectangle r, point p);
#endif
