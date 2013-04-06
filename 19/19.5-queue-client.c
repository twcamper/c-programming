#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "queue.h"

int main(void)
{
  Queue q1, q2;
  int n;

  srand((unsigned) time(NULL));

  q1 = create_queue();
  q2 = create_queue();

  insert_item(q1, 1);
  insert_item(q1, 2);

  n = remove_item(q1);
  printf("Removed %d from q1\n", n);
  insert_item(q2, n);
  n = remove_item(q1);
  printf("Removed %d from q1\n", n);
  insert_item(q2, n);

  assert(is_empty(q1));
  assert(!is_empty(q2));

  for (int i = 0; i < 1024; i++)
    insert_item(q1, rand() % INT_MAX);

  while (!is_empty(q1))
    printf("rear: %d, removed from front: %d\n", rear(q1), remove_item(q1));
  while (!is_empty(q2))
    printf("Removed %d from q2\n", remove_item(q2));

  insert_item(q2, 3);
  clear(q2);
  if (is_empty(q2))
    printf("q2 is empty\n");
  else
    printf("q2 is not empty\n");

  destroy(q1);
  destroy(q2);

  return 0;
}
