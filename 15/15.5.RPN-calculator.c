#include <stdio.h>
#include "evaluate-rpn-expression.h"
#include "stack.h"

int main(void)
{
  printf("%d\n", FRUMIOUS);
  tokenize();
  evaluate();
  pop();
  return 0;
}
