#include "parts.h"

typedef struct node {
  Part part;
  struct node *next;
} Node;
struct parts_type {
  size_t count;
  struct node *head;
};
Parts new_db(size_t initial_size)
{
  if (initial_size)
    ;
    /* Taking this arg is a hack to stay polymorphic while enabling
     * variable initial sizes for the array
     * implementations.
     *
     * The empty if just quiets the compiler.
     */
  Parts db = malloc(sizeof(struct parts_type));
  if (db == NULL)
    memory_error(__FILE__, __LINE__, __func__);

  db->count = 0;
  db->head = NULL;

  return db;
}
static void destroy_node(Node *n)
{
  destroy_part(n->part);
  free(n);
}
static void destroy_nodes(Parts db)
{
  Node *next;
  for (Node *n = db->head; n; n = next) {
    next = n->next;
    destroy_node(n);
  }
}
void destroy_db(Parts db)
{
  destroy_nodes(db);
  free(db);
}
static Node *create_node(Part p)
{
  Node *new_node = malloc(sizeof(Node));
  if (!new_node)
    memory_error(__FILE__, __LINE__, __func__);

  new_node->part = p;
  new_node->next = NULL;
  return new_node;
}
int insert_part(Parts db, Part p)
{
  /* invalid record? */
  if (!p)
    return -3;

  Node *cur, *prev;
  for (cur = db->head, prev = NULL;
       cur != NULL && get_part_number(p) > get_part_number(cur->part);
       prev = cur, cur = cur->next)
    ;
  /* duplicate part number? */
  if (cur != NULL && get_part_number(p) == get_part_number(cur->part))
    return -2;

  Node *n = create_node(p);
  n->next = cur;
  if (prev == NULL)
    db->head = n;
  else
    prev->next = n;

  db->count++;
  return 0;

}
int delete_part(Parts db, PartNumber number)
{
  Node *cur, *prev;

  for (cur = db->head, prev = NULL;
       cur != NULL && number != get_part_number(cur->part);
       prev = cur, cur = cur->next)
    ;
  if (cur == NULL) /* not found */
    return -1;
  if (prev == NULL)  /* first */
    db->head = db->head->next;
  else
    prev->next = cur->next;

  destroy_node(cur);
  db->count--;
  return 0;
}
Part find_part(Parts db, PartNumber part_number)
{
  for (Node *n = db->head; n != NULL; n = n->next)
    if (get_part_number(n->part) == part_number)
      return n->part;

  return NULL;
}
void iterate(Parts db, void (*op)(Part p))
{
  for (Node *n = db->head; n != NULL; n = n->next)
    op(n->part);
}
size_t size(Parts db)
{
  return db->count;
}
static Node *approximate_node(Parts db, PartNumber part_number)
{
  PartNumber pn;
  Node *previous, *current;

  if (db->count == 0)
    return NULL;

  /* return first if the target is smaller than all */
  if (get_part_number(db->head->part) > part_number)
    return db->head;

  /* find whichever the exact part or the next greatest */
  current = db->head;
  while ( current && (pn = get_part_number(current->part)) < part_number) {
    previous = current;
    current  = current->next;
  }
  /* return the exact part or the next smallest */
  if (pn == part_number)
    return current;
  else
    return previous;
}
void iterate_by_page(Parts db, size_t page_size, void (*record_op)(Part), int(*interval_op)(void))
{
  if (db->count == 0)
    return;

  int rc = 0;
  Node *n;
  size_t i;
  /* print first outside of loop to avoid a pause after the first;
   * otherwise we'd have to test for > 0 every iteration
   */
  record_op(db->head->part);
  for (i = 1, n = db->head->next; n != NULL; n = n->next, i++) {
    if (i % page_size == 0) {
      if ((rc = interval_op()) == -2) {
        return;
      } else if (rc == -3) {
        continue; /* 'end' function will require doubly linked list */
      } else if (rc > -1) {
        n = approximate_node(db, rc);
      }
    }
    record_op(n->part);
  }
}
Part approximate_part(Parts db, PartNumber part_number)
{
  if (db->count == 0)
    return NULL;

  return approximate_node(db, part_number)->part;
}
int write_db(char *filename, Parts db, char *write_mode)
{
  FILE *ostream;
  size_t record_size = get_part_record_size();
  if ((ostream = fopen(filename, write_mode)) == NULL) {
    print_error(__FILE__, filename);
    return -1;
  }

  for (Node *n = db->head; n != NULL; n = n->next) {
    if ((fwrite(n->part, record_size, 1, ostream) < 1) || (ferror(ostream)))
      return -2;
  }

  if (fclose(ostream) == EOF)
    return -3;

  return 0;
}
/* append contents to file and reset count to 0 */
int flush_to_disk(char *file, Parts db)
{
  int rc = 0;
  if ((rc = write_db(file, db, "ab")) == 0) {
    destroy_nodes(db);
    db->head  = NULL;
    db->count = 0;
  }

  return rc;
}
int read_to_db(Parts db, FILE *fp,  off_t record_size)
{
  Node *n;
  Part p;
  for (;;)  {
    p = new_part();
    if (fread(p, record_size, 1, fp) < 1) {
      destroy_part(p);
      if (ferror(fp))
        return -1;
      break;
    }
    if (db->head) {
      n->next = create_node(p);
      n = n->next;
    } else {
      db->head = create_node(p);
      n = db->head;
    }
    db->count++;
  }

  return 0;
}
