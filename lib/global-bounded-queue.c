#include "global-queue.h"
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX 5

struct Queue {
  int size;
  int front_position;
  int empty_position;
  Item data[QUEUE_MAX];
};

static struct Queue _queue = {0, 0, 0, {0}};
static void exit_queue_underflow(char *file, unsigned line, const char *function)
{
  fprintf(stderr, "Queue Underflow Error (attempt to read from empty queue): %s:%d (%s)\n", file, line, function);
  exit(EXIT_FAILURE);
}
static void increment_empty_position(void)
{
  _queue.empty_position++;
  if (_queue.empty_position >= QUEUE_MAX)
    _queue.empty_position = 0;
}
static void increment_queue_size(void)
{
  _queue.size++;
  if (_queue.size > QUEUE_MAX)
    _queue.size = 1;
}
static void increment_front_position(void)
{
  _queue.front_position++;
  if (_queue.front_position >= QUEUE_MAX)
    _queue.front_position = 0;
}

void insert_item(Item i)
{
  _queue.data[_queue.empty_position] = i;
  increment_empty_position();
  increment_queue_size();
}
Item remove_item(void)
{
  if (_queue.size < 1)
    exit_queue_underflow(__FILE__, __LINE__, __func__);

  Item item = _queue.data[_queue.front_position];
  increment_front_position();
  _queue.size--;
  return item;
}
Item front(void)
{
  if (_queue.size < 1)
    exit_queue_underflow(__FILE__, __LINE__, __func__);
  return _queue.data[_queue.front_position];
}
Item rear(void)
{
  if (_queue.size < 1)
    exit_queue_underflow(__FILE__, __LINE__, __func__);
  return _queue.data[_queue.front_position + _queue.size - 1];
}
bool is_empty(void)
{
  return _queue.size == 0;
}
void clear_queue(void)
{
  _queue.front_position = 0;
  _queue.size =  0;
  _queue.empty_position = 0;
}
int queue_size(void)
{
  return _queue.size;
}
