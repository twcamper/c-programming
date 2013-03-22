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
  if (is_empty()) {
    fprintf(stderr, "Stack Underflow\n");
    exit(EXIT_FAILURE);
  }

  int temp_value = top->value;
  delete_head();
  return temp_value;
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
#include <limits.h>

int push_items_test(void)
{
  _assert(push(1) == true);
  _assert(top->value == 1);
  _assert(top->next == NULL);

  _assert(push(INT_MAX) == true);
  _assert(top->value == INT_MAX);
  _assert(top->next->value == 1);
  _assert(top->next->next == NULL);

  _assert(push(3) == true);
  _assert(top->value == 3);
  _assert(top->next->value == INT_MAX);
  _assert(top->next->next->value == 1);
  _assert(top->next->next->next == NULL);

  empty_the_stack();

  return 0;
}
int pop_test(void)
{
  push(1);
  push(2);
  push(3);

  _assert(pop() == 3);
  _assert(top->value == 2);
  _assert(top->next->value == 1);
  _assert(top->next->next == NULL);

  _assert(pop() == 2);
  _assert(top->value == 1);
  _assert(top->next == NULL);

  _assert(pop() == 1);
  _assert(top == NULL);

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

  push(34);
  push(87);
  push(12345);
  push(0);
  push(-687);

  empty_the_stack();
  _assert(top == NULL);
  _assert(is_empty());
  return 0;
}

int all_tests(void)
{
  _run(push_items_test);
  _run(is_empty_test);
  _run(pop_test);
  _run(empty_the_stack_test);
  return 0;
}
#else
int pop_from_empty_stack_test(void)
{
  printf("We should exit with an error: echo $? should return %d\n", EXIT_FAILURE);
  push(63);
  pop();
  pop();

  return 0;
}

int main(void)
{

  pop_from_empty_stack_test();
  return 0;
}
#endif
