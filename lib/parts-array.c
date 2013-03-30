#include "parts.h"
#define INITIAL_SIZE 30

struct parts_type {
  int count;
  Part *rows;
  size_t requested_row_allocation;
};

Parts new_db()
{
  Parts db = malloc(sizeof(struct parts_type));
  if (db == NULL)
    memory_error(__FILE__, __LINE__, __func__);

  db->count = 0;
  db->requested_row_allocation = INITIAL_SIZE;
  db->rows = malloc(db->requested_row_allocation * sizeof(Part));

  if (db->rows == NULL)
    memory_error(__FILE__, __LINE__, __func__);

  return db;
}
void destroy_db(Parts db)
{
  for (int i = 0; i < db->count; i++)
    free(db->rows[i]);

  free(db->rows);
  free(db);
}
int size(Parts db)
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
int insert_part(Parts db, Part p)
{
  int i, j;

  if (db->count == (int)db->requested_row_allocation)
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
  int i;
  for (i = 0; i < db->count; i++)
    if (get_part_number(db->rows[i]) == part_number)
      return db->rows[i];
  return NULL;
}
void iterate(Parts db, void (*op)(Part p))
{
  for (int i = 0; i < db->count; i++)
    op(db->rows[i]);
}
