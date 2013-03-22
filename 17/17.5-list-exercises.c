#include "test_runner.h"
#include <stdlib.h>

typedef struct node {
  int value;
  struct node *next;
} Node;

Node *create(int value)
{
  Node *n;
  if ((n = malloc(sizeof(Node))) == NULL) {
    fprintf(stderr, "malloc failed: %s:%d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  /* printf("malloc: %p\n", n); */
  n->value = value;
  return n;
}
Node *add(Node *list, int value)
{
  Node *new = create(value);
  new->next = list;
  return new;
}
Node *create_list(int a[], int n)
{
  Node *first = create(a[0]);
  for (int i = 1; i < n; i++) {
    first = add(first, a[i]);
  }
  return first;
}
Node *insert_17_5_13(Node *head, Node *new_node)
{
  Node *cur = head, *prev = NULL;
  while (cur != NULL && cur->value < new_node->value)  {
    prev = cur;
    cur  = cur->next;
  }
  if (cur == head) {  /* insert at beginning */
    new_node->next = head;
    head           = new_node;
  } else {
    if (cur != NULL) {  /* into middle (current is not final node) */
      new_node->next = cur;
    }
    prev->next = new_node;
  }
  return head;
}
void free_list(Node *head)
{
  Node *next = NULL;
  for (Node *n = head; n; n = next) {
    next = n->next;
    /* printf("free: %p\n", n); */
    free(n);
  }
}
int create_list_test(void)
{
  Node *list = create_list((int[]){11, 22, 33}, 3);
  _assert(list->next != NULL);
  _assert(list->value == 33);
  _assert(list->next->value == 22);
  _assert(list->next->next->value == 11);
  _assert(list->next->next->next == NULL);
  free_list(list);
  return 0;
}

int insert_before_test(void)
{
  Node *list = create_list((int[]){11, 10}, 2);
  Node *n = create(9);
  list = insert_17_5_13(list, n);

  _assert(list->value == 9);
  _assert(list->next->value == 10);

  return 0;
}
int insert_after_test(void)
{
  Node *list = create_list((int[]){11, 10}, 2);
  Node *n = create(12);
  list = insert_17_5_13(list, n);

  _assert(list->value == 10);
  _assert(list->next->value == 11);
  _assert(list->next->next->value == 12);

  return 0;
}
int insert_middle_test(void)
{
  Node *list = create_list((int[]){5, 3}, 2);
  Node *n = create(4);
  list = insert_17_5_13(list, n);

  _assert(list->value == 3);
  _assert(list->next->value == 4);
  _assert(list->next->next->value == 5);

  return 0;
}
int all_tests(void)
{
  _run(create_list_test);
  _run(insert_before_test);
  _run(insert_after_test);
  _run(insert_middle_test);
  return 0;
}
