#include "queue.h"
#include "test_runner.h"

int insert_item_test(void)
{
  Queue q = create_queue();

  _assert(depth(q) == 0);
  insert_item(q,42);
  _assert(front(q) == 42);
  _assert(rear(q) == 42);
  _assert(depth(q) == 1);

  insert_item(q,10);
  _assert(front(q) == 42);
  _assert(rear(q) == 10);
  _assert(depth(q) == 2);

  insert_item(q,-1);
  _assert(front(q) == 42);
  _assert(rear(q) == -1);
  _assert(depth(q) == 3);

  destroy(q);
  return 0;
}
int remove_item_test(void)
{
  Queue q = create_queue();

  insert_item(q,42);
  _assert(front(q) == 42);
  _assert(depth(q) == 1);

  _assert(remove_item(q) == 42);
  _assert(depth(q) == 0);
  _assert(is_empty(q) == true);

  insert_item(q,12);
  insert_item(q,13);
  insert_item(q,14);

  _assert(front(q) == 12);
  _assert(rear(q) == 14);
  _assert(depth(q) == 3);

  _assert(remove_item(q) == 12);
  _assert(front(q) == 13);
  _assert(rear(q) == 14);
  _assert(depth(q) == 2);

  _assert(remove_item(q) == 13);
  _assert(front(q) == 14);
  _assert(rear(q) == 14);
  _assert(depth(q) == 1);

  destroy(q);
  return 0;
}
int all_tests(void)
{
  _run(insert_item_test);
  _run(remove_item_test);

  return 0;
}
