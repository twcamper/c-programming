#include <assert.h>
#include "rectangle.h"

int main(void)
{
  rectangle R = {
    (point) {1,1},
    (point) {10,10}
  };
  assert(area(R) == 0);
  assert(center(R) == 0);
  return 0;
}
