#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  struct point { int x, y; };
  struct rectangle { struct point upper_left, lower_right; };
  struct rectangle *p;

  p = malloc(sizeof(struct rectangle));
  p->upper_left = (struct point){10,25};
  p->lower_right = (struct point){20,15};

  return 0;
}
