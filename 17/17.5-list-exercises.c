#include "test_runner.h"
#include <stdlib.h>

typedef struct node {
  int value;
  struct node *next;
} node;

node *create(void)
{
  node *n;
  if ((n = malloc(sizeof(node))) == NULL) {
    fprintf(stderr, "malloc failed: %s:%d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  /* printf("malloc: %p\n", n); */
  return n;
}
node *add(node *list, int value)
{
  node *new = create();
  new->value = value;
  new->next = list;
  return new;
}
node *create_list(int a[], int n)
{
  node *first = create();
  first->value = a[0];
  for (int i = 1; i < n; i++) {
    first = add(first, a[i]);
  }
  return first;
}
void free_list(node *head)
{
  node *next = NULL;
  for (node *n = head; n; n = next) {
    next = n->next;
    /* printf("free: %p\n", n); */
    free(n);
  }
}
int create_list_test(void)
{
  node *list = create_list((int[]){11, 22, 33}, 3);
  _assert(list->next != NULL);
  _assert(list->value == 33);
  _assert(list->next->value == 22);
  _assert(list->next->next->value == 11);
  _assert(list->next->next->next == NULL);
  free_list(list);
  return 0;
}

int all_tests(void)
{
  _run(create_list_test);
  return 0;
}
