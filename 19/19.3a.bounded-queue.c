#include <stdio.h>
#include <assert.h>
#include "bounded-queue.h"

int main(void)
{
  Queue q = create_queue(37);
  insert_item(q, 2);
  assert(remove_item(q) == 2);
  assert(is_empty(q) == true);

  printf("This should exit with a failure.\n\n");
  /* remove_item(q); */
  front(q);
  rear(q);

  return 0;
}
