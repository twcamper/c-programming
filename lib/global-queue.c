#include "global-queue.h"

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
