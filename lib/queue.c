#include "queue.h"
#include "error.h"
#include <stdlib.h>

typedef struct node
{
  Item item;
  struct node *next;
} Node;

struct queue_type
{
  Node *front;
  Node *rear;
  int depth;
};

static Node * create_node(Item value)
{
  Node *n = malloc(sizeof(Node));
  if (!n)
    memory_error(__FILE__, __LINE__, __func__);

  n->item = value;
  n->next = NULL;
  return n;
}
Queue create_queue(void)
{
  Queue q = malloc(sizeof(struct queue_type));
  if (!q)
    memory_error(__FILE__, __LINE__, __func__);

  q->front = NULL;
  q->rear  = NULL;
  q->depth = 0;
  return q;
}

void insert_item(Queue q, Item i)
{
  if (q->depth == 0) {
    q->front       = create_node(i);
    q->rear        = q->front;
  } else {
    q->rear->next  = create_node(i);
    q->rear        = q->rear->next;
  }

  q->depth++;
}
Item remove_item(Queue q)
{
  Node *old_front = q->front;
  Item value = old_front->item;
  q->front = q->front->next;
  free(old_front);
  q->depth--;
  return value;
}
Item front(Queue q)
{
  return q->front->item;
}
Item rear(Queue q)
{
  return q->rear->item;
}
bool is_empty(Queue q)
{
  return q->depth == 0;
}
void destroy(Queue q)
{
  Node *next = NULL;
  for (Node *n = q->front; n; n = next) {
    next = n->next;
    free(n);
  }
  free(q);
}
int depth(Queue q)
{
  return q->depth;
}
