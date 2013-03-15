#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdbool.h>

typedef struct {int x, y;} point;
typedef struct {point upper_left, lower_right; } rectangle;

int area(rectangle r);
point center(rectangle r);
rectangle move(rectangle r, int x, int y);
bool is_inside(rectangle r, point p);
int height(rectangle r);
int width(rectangle r);
#endif
