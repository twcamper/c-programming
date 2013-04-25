#include "parts.h"
#define INITIAL_SIZE 30

struct parts_type {
  size_t count;
  Part *rows;
  size_t requested_row_allocation;
};

Parts new_db(size_t initial_size)
{
  Parts db = malloc(sizeof(struct parts_type));
  if (db == NULL)
    memory_error(__FILE__, __LINE__, __func__);

  db->count = 0;
  db->requested_row_allocation = initial_size;
  db->rows = malloc(db->requested_row_allocation * sizeof(Part));

  if (db->rows == NULL)
    memory_error(__FILE__, __LINE__, __func__);

  return db;
}
void destroy_db(Parts db)
{
  for (size_t i = 0; i < db->count; i++)
    free(db->rows[i]);

  free(db->rows);
  free(db);
}
size_t size(Parts db)
{
  return db->count;
}
static int resize_db_17_1(Parts db)
{
  db->requested_row_allocation *= 2;
  Part *temp = realloc(db->rows, db->requested_row_allocation * sizeof(Part));
  if (temp == NULL)
    return -1;

  db->rows = temp;
  return 0;
}
int delete_part(Parts db, PartNumber number)
{
  size_t i;

  for (i = 0; i < db->count; i++)
    if (get_part_number(db->rows[i]) == number)
      break;

  /* not found */
  if (i == db->count)
    return -1;

  destroy_part(db->rows[i]);
  db->rows[i] = NULL;

  for (;i < db->count; i++)
    db->rows[i] = db->rows[i + 1];

  db->rows[i] = NULL;
  db->count--;
  return 0;
}
int insert_part(Parts db, Part p)
{
  size_t i, j;

  if (db->count == db->requested_row_allocation)
    if ((resize_db_17_1(db) != 0)) {
      return -1;
    }
  /* invalid record? */
  if (!p)
    return -3;

  /* find position to insert new record */
  for (i = 0; i < db->count && get_part_number(db->rows[i]) <= get_part_number(p); i++)
    if (get_part_number(db->rows[i]) == get_part_number(p))
      return -2;  /* duplicate record */

  /* shift remaining records down by 1 */
  for (j = db->count; j > i; j--)
    db->rows[j] = db->rows[j-1];
  /* insert our new record in the newly vacant hole */
  db->rows[i] = p;
  db->count++;
  return 0;
}
/**********************************************************
 * find_part: Looks up a part number in the inventory     *
 *            array. Returns the array index if the part  *
 *            number is found; otherwise, returns -1.     *
 **********************************************************/
Part find_part(Parts db, PartNumber part_number)
{
  size_t i;
  for (i = 0; i < db->count; i++)
    if (get_part_number(db->rows[i]) == part_number)
      return db->rows[i];
  return NULL;
}
void iterate(Parts db, void (*op)(Part p))
{
  for (size_t i = 0; i < db->count; i++)
    op(db->rows[i]);
}
Part approximate_part(Parts db, PartNumber part_number)
{
  size_t i = 0;
  PartNumber pn;

  if (db->count == 0)
    return NULL;

  /* return first if the target is smaller than all */
  if (get_part_number(db->rows[0]) > part_number)
    return db->rows[0];

  /* find whichever the exact part or the next greatest */
  while ( i < db->count && (pn = get_part_number(db->rows[i])) < part_number)
     ++i;
  /* return the exact part or the next smallest */
  return db->rows[(pn == part_number ? i : i - 1)];
}
