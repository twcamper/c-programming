#include "queue.h"

#define QUEUE_ALLOCATION 10

struct Queue {
  Item data[QUEUE_ALLOCATION];
  int front;
  int size;
  int next_empty;
};

static struct Queue _queue = {{0}, 0, 0, 0};

void insert_item(Item i)
{
  _queue.data[_queue.next_empty] = i;
  _queue.next_empty++;
  _queue.size++;
}
Item remove_item(void)
{
  _queue.size--;
  return _queue.data[_queue.front++];
}
Item front(void)
{
  return _queue.data[_queue.front];
}
Item rear(void)
{
  return _queue.data[_queue.next_empty - 1];
}
bool is_empty(void)
{
  return _queue.size == 0;
}
void clear_queue(void)
{
  _queue.front = _queue.size = _queue.next_empty = 0;
  for (int i = 0; i < QUEUE_ALLOCATION; i++)
    _queue.data[i] = 0;
}
int queue_size(void)
{
  return _queue.size;
}

#ifdef TEST
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
#else
int main(void)
{

  return 0;
}
#endif
