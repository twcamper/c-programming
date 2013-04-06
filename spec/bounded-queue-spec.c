#include "bounded-queue.h"
#include "test_runner.h"

int insert_item_test(void)
{
  Queue q = create_queue(5);
  _assert(depth(q) == 0);
  insert_item(q, 42);
  _assert(front(q) == 42);
  _assert(rear(q) == 42);
  _assert(depth(q) == 1);

  insert_item(q, 10);
  _assert(front(q) == 42);
  _assert(rear(q) == 10);
  _assert(depth(q) == 2);

  insert_item(q, -1);
  _assert(front(q) == 42);
  _assert(rear(q) == -1);
  _assert(depth(q) == 3);

  destroy(q);
  return 0;
}
int insert_item_overflow_test(void)
{
  Queue q = create_queue(5);
  insert_item(q, 1);
  insert_item(q, 2);
  insert_item(q, 3);
  insert_item(q, 4);
  insert_item(q, 5);
  _assert(front(q) == 1);
  _assert(rear(q) == 5);

  /* wrapping back around to front */
  insert_item(q, 6);
  _assert(front(q) == 6);
  _assert(rear(q) == 6);
  _assert(depth(q) == 1);

  destroy(q);
  return 0;
}
int remove_item_test(void)
{
  Queue q = create_queue(5);
  insert_item(q, 42);
  _assert(front(q) == 42);
  _assert(depth(q) == 1);

  _assert(remove_item(q) == 42);
  _assert(depth(q) == 0);
  _assert(is_empty(q) == true);

  insert_item(q, 12);
  insert_item(q, 13);
  insert_item(q, 14);

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
int remove_item_past_upper_bound_test(void)
{
  Queue q = create_queue(5);
  insert_item(q, 200);
  _assert(rear(q) == 200);
  _assert(remove_item(q) == 200);
  _assert(is_empty(q) == true);

  insert_item(q, 201);
  _assert(rear(q) == 201);
  _assert(remove_item(q) == 201);
  _assert(is_empty(q) == true);

  insert_item(q, 202);
  _assert(rear(q) == 202);
  _assert(remove_item(q) == 202);
  _assert(is_empty(q) == true);

  insert_item(q, 203);
  _assert(rear(q) == 203);
  _assert(remove_item(q) == 203);
  _assert(is_empty(q) == true);

  insert_item(q, 101);
  _assert(rear(q) == 101);
  _assert(remove_item(q) == 101);
  _assert(is_empty(q) == true);

  insert_item(q, 102);
  _assert(rear(q) == 102);
  _assert(remove_item(q) == 102);
  _assert(is_empty(q) == true);

  insert_item(q, 103);
  _assert(rear(q) == 103);
  _assert(remove_item(q) == 103);
  _assert(is_empty(q) == true);

  destroy(q);
  return 0;
}
int remove_item_past_upper_bound_test2(void)
{
  Queue q = create_queue(5);
  insert_item(q, 200);
  insert_item(q, 201);
  insert_item(q, 202);
  insert_item(q, 203);
  insert_item(q, 204);

  _assert(remove_item(q) == 200);
  _assert(front(q) == 201);
  _assert(rear(q) == 204);
  _assert(remove_item(q) == 201);
  _assert(front(q) == 202);
  _assert(rear(q) == 204);
  _assert(remove_item(q) == 202);
  _assert(front(q) == 203);
  _assert(rear(q) == 204);
  _assert(remove_item(q) == 203);
  _assert(front(q) == 204);
  _assert(rear(q) == 204);
  _assert(remove_item(q) == 204);
  _assert(is_empty(q) == true);

  insert_item(q, 102);
  _assert(rear(q) == 102);
  insert_item(q, 103);
  _assert(front(q) == 102);
  _assert(rear(q) == 103);

  _assert(remove_item(q) == 102);
  _assert(rear(q) == 103);
  _assert(remove_item(q) == 103);
  _assert(is_empty(q) == true);

  destroy(q);
  return 0;
}
int all_tests(void)
{
  _run(insert_item_test);
  _run(insert_item_overflow_test);
  _run(remove_item_test);
  _run(remove_item_past_upper_bound_test);
  _run(remove_item_past_upper_bound_test2);

  return 0;
}
