#include "bounded-queue.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

struct queue_type {
  int depth;
  int max_depth;
  int front_position;
  int empty_position;
  Item *data;
};

static void exit_queue_underflow(char *file, unsigned line, const char *function)
{
  fprintf(stderr, "Queue Underflow Error (attempt to read from empty queue): %s:%d (%s)\n", file, line, function);
  exit(EXIT_FAILURE);
}

static void increment_empty_position(Queue q)
{
  q->empty_position++;
  if (q->empty_position >= q->max_depth)
    q->empty_position = 0;
}
static void increment_queue_size(Queue q)
{
  q->depth++;
  if (q->depth > q->max_depth)
    q->depth = 1;
}
static void increment_front_position(Queue q)
{
  q->front_position++;
  if (q->front_position >= q->max_depth)
    q->front_position = 0;
}

Queue create_queue(int max_depth)
{
  Queue q = malloc(sizeof(struct queue_type));
  if (!q)
    memory_error(__FILE__, __LINE__, __func__);

  q->depth = 0;
  q->max_depth = max_depth;
  q->front_position = 0;
  q->empty_position = 0;

  q->data = malloc(max_depth * sizeof(Item));
  if (!q->data)
    memory_error(__FILE__, __LINE__, __func__);

  return q;
}
void destroy(Queue q)
{
  free(q->data);
  free(q);
}
void insert_item(Queue q, Item i)
{
  q->data[q->empty_position] = i;
  increment_empty_position(q);
  increment_queue_size(q);
}
Item remove_item(Queue q)
{
  if (q->depth < 1) {
    destroy(q);
    exit_queue_underflow(__FILE__, __LINE__, __func__);
  }

  Item item = q->data[q->front_position];
  increment_front_position(q);
  q->depth--;
  return item;
}
Item front(Queue q)
{
  if (q->depth < 1) {
    destroy(q);
    exit_queue_underflow(__FILE__, __LINE__, __func__);
  }
  return q->data[q->front_position];
}
Item rear(Queue q)
{
  if (q->depth < 1) {
    destroy(q);
    exit_queue_underflow(__FILE__, __LINE__, __func__);
  }
  return q->data[q->front_position + q->depth - 1];
}
bool is_empty(Queue q)
{
  return q->depth == 0;
}
void clear_queue(Queue q)
{
  q->front_position = 0;
  q->depth =  0;
  q->empty_position = 0;
}
int depth(Queue q)
{
  return q->depth;
}
