#include "global-queue.h"
#include "test_runner.h"

int insert_item_test(void)
{
  clear_queue();
  _assert(queue_size() == 0);
  insert_item(42);
  _assert(front() == 42);
  _assert(rear() == 42);
  _assert(queue_size() == 1);

  insert_item(10);
  _assert(front() == 42);
  _assert(rear() == 10);
  _assert(queue_size() == 2);

  insert_item(-1);
  _assert(front() == 42);
  _assert(rear() == -1);
  _assert(queue_size() == 3);
  return 0;
}
int insert_item_overflow_test(void)
{
  clear_queue();
  insert_item(1);
  insert_item(2);
  insert_item(3);
  insert_item(4);
  insert_item(5);
  _assert(front() == 1);
  _assert(rear() == 5);

  /* wrapping back around to front */
  insert_item(6);
  _assert(front() == 6);
  _assert(rear() == 6);
  _assert(queue_size() == 1);

  return 0;
}
int remove_item_test(void)
{
  clear_queue();
  insert_item(42);
  _assert(front() == 42);
  _assert(queue_size() == 1);

  _assert(remove_item() == 42);
  _assert(queue_size() == 0);
  _assert(is_empty() == true);

  insert_item(12);
  insert_item(13);
  insert_item(14);

  _assert(front() == 12);
  _assert(rear() == 14);
  _assert(queue_size() == 3);

  _assert(remove_item() == 12);
  _assert(front() == 13);
  _assert(rear() == 14);
  _assert(queue_size() == 2);

  _assert(remove_item() == 13);
  _assert(front() == 14);
  _assert(rear() == 14);
  _assert(queue_size() == 1);

  return 0;
}
int remove_item_past_upper_bound_test(void)
{
  clear_queue();
  insert_item(200);
  _assert(remove_item() == 200);
  _assert(is_empty() == true);

  insert_item(201);
  _assert(remove_item() == 201);
  _assert(is_empty() == true);

  insert_item(202);
  _assert(remove_item() == 202);
  _assert(is_empty() == true);

  insert_item(203);
  _assert(remove_item() == 203);
  _assert(is_empty() == true);

  insert_item(101);
  _assert(remove_item() == 101);
  _assert(is_empty() == true);

  insert_item(102);
  _assert(remove_item() == 102);
  _assert(is_empty() == true);

  insert_item(103);
  _assert(remove_item() == 103);
  _assert(is_empty() == true);

  return 0;
}
int remove_item_past_upper_bound_test2(void)
{
  clear_queue();
  insert_item(200);
  insert_item(201);
  insert_item(202);
  insert_item(203);
  insert_item(204);

  _assert(remove_item() == 200);
  _assert(remove_item() == 201);
  _assert(remove_item() == 202);
  _assert(remove_item() == 203);
  _assert(remove_item() == 204);
  _assert(is_empty() == true);

  insert_item(102);
  insert_item(103);
  _assert(front() == 102);
  _assert(rear() == 103);

  _assert(remove_item() == 102);
  _assert(remove_item() == 103);
  _assert(is_empty() == true);

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
