#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/* A Queue is a pointer to queue_type struct */
typedef struct queue_type *Queue;
typedef int Item;

Queue create(void);
void destroy(Queue q);
void insert(Queue q, Item i);
Item remove(Queue q);
Item front(Queue q);
Item rear(Queue q);
bool is_empty(Queue q);

#endif
