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
  /* printf("malloc: %p, %d\n", n, value); */
  n->value = value;
  n->next  = NULL;
  return n;
}
void add(Node **list, int value)
{
  Node *new = create(value);
  new->next = *list;
  *list     = new;
}
Node *create_list(int a[], int n)
{
  Node *first = create(a[0]);
  for (int i = 1; i < n; i++) {
    add(&first, a[i]);
  }
  return first;
}
void delete_17_6_14(Node **list, int n)
{
  Node *cur, *prev;

  for (cur = *list, prev = NULL;
       cur != NULL && cur->value != n;
       prev = cur, cur = cur->next)
    ;
  if (cur == NULL)
    return;
  if (prev == NULL)
    *list = (*list)->next;
  else
    prev->next = cur->next;
  free(cur);
}
void insert_17_5_13(Node **head, Node *new_node)
{
  Node *cur = *head, *prev = NULL;
  while (cur != NULL && cur->value < new_node->value)  {
    prev = cur;
    cur  = cur->next;
  }
  if (cur == *head) {  /* insert at beginning */
    new_node->next = *head;
    *head           = new_node;
  } else {
    if (cur == NULL) { /* appending at end */
      new_node->next = NULL;
    } else {           /* into middle (current is not final node) */
      new_node->next = cur;
    }
    prev->next = new_node;
  }
}
int count_occurrences_17_5_11(Node *head, int n)
{
  int count = 0;
  for (Node *node = head; node; node = node->next)
    if (node-> value == n)
      count++;

  return count;
}
Node *find_last_17_5_12(Node *head, int n)
{
  Node *target = NULL;
  for (Node *node = head; node; node = node->next)
    if (node-> value == n)
      target = node;

  return target;
}
void free_list(Node *head)
{
  Node *next = NULL;
  for (Node *n = head; n; n = next) {
    next = n->next;
    /* printf("  free: %p, %d\n", n, n->value); */
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
  insert_17_5_13(&list, n);

  _assert(list->value == 9);
  _assert(list->next->value == 10);
  free_list(list);

  return 0;
}
int insert_after_test(void)
{
  Node *list = create_list((int[]){11, 10}, 2);
  Node *n = create(12);
  insert_17_5_13(&list, n);

  _assert(list->value == 10);
  _assert(list->next->value == 11);
  _assert(list->next->next->value == 12);
  _assert(list->next->next->next == NULL);
  free_list(list);

  return 0;
}
int insert_middle_test(void)
{
  Node *list = create_list((int[]){5, 3}, 2);
  Node *n = create(4);
  insert_17_5_13(&list, n);

  _assert(list->value == 3);
  _assert(list->next->value == 4);
  _assert(list->next->next->value == 5);
  _assert(list->next->next->next == NULL);
  free_list(list);

  return 0;
}
int count_occurrences_test(void)
{
  Node *list = create_list((int[]){5, 3, 5, 34, 989, 5, 13, -5, 3, 5, 0, 400}, 12);
  _assert(count_occurrences_17_5_11(list, 5) == 4);
  _assert(count_occurrences_17_5_11(list, 3) == 2);
  _assert(count_occurrences_17_5_11(list, 989) == 1);
  _assert(count_occurrences_17_5_11(list, 988) == 0);
  free_list(list);

  return 0;
}

int find_last_test(void)
{

  Node *list = create_list((int[]){5, 3, 5, 34}, 4);
  _assert(find_last_17_5_12(list, 6) == NULL);
  _assert(find_last_17_5_12(list, 3)->value == 3);
  _assert(find_last_17_5_12(list, 3)->next->value == 5);
  _assert(find_last_17_5_12(list, 34)->next->value == 5);
  _assert(find_last_17_5_12(list, 34)->next->next->value == 3);
  _assert(find_last_17_5_12(list, 5)->next == NULL);
  free_list(list);
  return 0;
}
int delete_empty_test(void)
{
  Node *list = NULL;
  delete_17_6_14(&list, 3);
  _assert(list == NULL);

  return 0;
}
int delete_not_found_test(void)
{
  Node *list = create_list((int[]) {9, 7}, 2);
  _assert(list->value == 7);
  _assert(list->next->value == 9);
  _assert(list->next->next == NULL);

  delete_17_6_14(&list, 6);

  _assert(list->value == 7);
  _assert(list->next->value == 9);
  _assert(list->next->next == NULL);
  free_list(list);

  return 0;
}
int delete_only_test(void)
{
  Node *list = create(3);

  _assert(list->value == 3);
  _assert(list->next == NULL);

  delete_17_6_14(&list, 3);

  _assert(list == NULL);

  return 0;
}
int delete_first_test(void)
{
  Node *list = create_list((int[]) {9, 7}, 2);
  _assert(list->value == 7);
  _assert(list->next->value == 9);
  _assert(list->next->next == NULL);

  delete_17_6_14(&list, 7);

  _assert(list->value == 9);
  _assert(list->next == NULL);
  free_list(list);
  return 0;
}
int delete_middle_test(void)
{
  Node *list = create_list((int[]) {9, 8, 7}, 3);
  _assert(list->value == 7);
  _assert(list->next->value == 8);
  _assert(list->next->next->value == 9);
  _assert(list->next->next->next == NULL);

  delete_17_6_14(&list, 8);

  _assert(list->value == 7);
  _assert(list->next->value == 9);
  _assert(list->next->next == NULL);
  free_list(list);
  return 0;
}
int delete_last_test(void)
{
  Node *list = create_list((int[]) {9, 7}, 2);
  _assert(list->value == 7);
  _assert(list->next->value == 9);
  _assert(list->next->next == NULL);

  delete_17_6_14(&list, 9);

  _assert(list->value == 7);
  _assert(list->next == NULL);
  free_list(list);
  return 0;
}
int all_tests(void)
{
  _run(create_list_test);
  _run(insert_before_test);
  _run(insert_after_test);
  _run(insert_middle_test);
  _run(delete_empty_test);
  _run(delete_not_found_test);
  _run(delete_only_test);
  _run(delete_first_test);
  _run(delete_middle_test);
  _run(delete_last_test);
  _run(count_occurrences_test);
  _run(find_last_test);
  return 0;
}
