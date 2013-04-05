#include <stdio.h>
#include <assert.h>
#include "global-queue.h"

int main(void)
{
  insert_item(2);
  assert(remove_item() == 2);
  assert(is_empty() == true);

  printf("This should exit with a failure.\n\n");
  /* remove_item(); */
  front();
  rear();

  return 0;
}
