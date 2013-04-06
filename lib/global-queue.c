#include "global-queue.h"
#include "error.h"
#include <stdlib.h>

typedef struct node
{
  Item item;
  struct node *next;
} Node;

struct Queue
{
  Node *front;
  Node *rear;
  int depth;
};

static struct Queue _queue = {.front = NULL, .rear = NULL, .depth = 0 };

static Node * create_node(Item value)
{
  Node *n = malloc(sizeof(Node));
  if (!n)
    memory_error(__FILE__, __LINE__, __func__);

  n->item = value;
  n->next = NULL;
  return n;
}

void insert_item(Item i)
{
  if (_queue.depth == 0) {
    _queue.front       = create_node(i);
    _queue.rear        = _queue.front;
  } else {
    _queue.rear->next  = create_node(i);
    _queue.rear        = _queue.rear->next;
  }

  _queue.depth++;
}
Item remove_item(void)
{
  Node *old_front = _queue.front;
  Item value = old_front->item;
  _queue.front = _queue.front->next;
  free(old_front);
  _queue.depth--;
  return value;
}
Item front(void)
{
  return _queue.front->item;
}
Item rear(void)
{
  return _queue.rear->item;
}
bool is_empty(void)
{
  return _queue.depth == 0;
}
void clear_queue(void)
{
  Node *next = NULL;
  for (Node *n = _queue.front; n; n = next) {
    next = n->next;
    free(n);
  }
  _queue.front = NULL;
  _queue.depth = 0;
  _queue.rear  = NULL;
}
int queue_size(void)
{
  return _queue.depth;
}
