#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef int Item;

void insert_item(Item i);
Item remove_item(void);
Item front(void);
Item rear(void);
bool is_empty(void);
void clear_queue(void);
int queue_size(void);

#endif
