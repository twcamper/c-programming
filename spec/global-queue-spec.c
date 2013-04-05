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
  insert_item(10);

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
int front_test(void)
{

  return 0;
}
int rear_test(void)
{

  return 0;
}
int is_empty_test(void)
{

  return 0;
}
int all_tests(void)
{
  _run(insert_item_test);
  _run(insert_item_overflow_test);
  _run(remove_item_test);
  _run(front_test);
  _run(rear_test);
  _run(is_empty_test);

  return 0;
}
