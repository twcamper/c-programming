#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct item {
  int value;
  struct item *next;
} Item;

Item *top = NULL;

bool push(int n);
int pop(void);
void empty_the_stack(void);
void delete_head(void);
bool is_empty(void);

bool is_empty(void)
{
  return top == NULL;
}

bool push(int n)
{
  Item *new_item;
  if ((new_item = malloc(sizeof(Item))) == NULL)
    return false;
  new_item->value = n;
  /* printf("malloc: %p: %d\n", new_item, new_item->value); */
  new_item->next = top;
  top = new_item;

  return true;
}

int pop(void)
{
  /*
   * if top is empty
   *   warn stack underflow
   *   exit fail
   * else
   *   assign top->value to temp_int
   *   delete head
   *   return temp_int
   */
  return 0;
}

void empty_the_stack(void)
{
  while (top)
    delete_head();
}

void delete_head(void)
{
  /*
   *  if top is not null
   *   assign address of structure pointed to by top to temp_item
   *   assign address of structure pointed to by top->next to top
   *   free temp_item
   */
  Item *temp;
  if (top) {
    temp = top;
    top = top->next;
    /* printf("  free: %p: %d\n", temp, temp->value); */
    free(temp);
  }
}
#ifdef TEST
#include "test_runner.h"
int push_items_test(void)
{
  _assert(push(1) == true);
  _assert(top->value == 1);
  _assert(top->next == NULL);

  _assert(push(2) == true);
  _assert(top->value == 2);
  _assert(top->next->value == 1);
  _assert(top->next->next == NULL);

  _assert(push(3) == true);
  _assert(top->value == 3);
  _assert(top->next->value == 2);
  _assert(top->next->next->value == 1);
  _assert(top->next->next->next == NULL);

  empty_the_stack();

  return 0;
}
int pop_item_test(void)
{

  return 0;
}
int pop_last_item_test(void)
{

  return 0;
}
int is_empty_test(void)
{
  _assert(is_empty() == true);
  push(1);
  _assert(is_empty() == false);
  empty_the_stack();
  return 0;
}
int empty_the_stack_test(void)
{

  return 0;
}

int all_tests(void)
{
  _run(push_items_test);
  _run(is_empty_test);

  return 0;
}
#else
int pop_from_empty_stack_test(void);

int main(void)
{

  return 0;
}
#endif
