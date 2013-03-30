#include "parts.h"

struct parts_type {
  int count;
  Part *rows;
  size_t requested_row_allocation;
};

Parts new_db(int size)
{
  Parts db = malloc(sizeof(struct parts_type));
  if (db == NULL)
    memory_error(__FILE__, __LINE__, __func__);

  db->count = 0;
  db->requested_row_allocation = size;
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
int update_part(Parts db, PartNumber number, PartQuantity change)
{
  Part p;
  if (!(p = find_part(db, number)))
    return -1;

  if (!set_part_on_hand(p, (get_part_on_hand(p) + change)))
    return -2;

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
void load(Parts db)
{
  insert_part(db, set_part(212, "Named Part, unlabled", 1));
  insert_part(db, set_part(12, "Flex Wing Grooming Mower", 19));
  insert_part(db, set_part(400, "Grommet", 18));
  insert_part(db, set_part(1, "Fern Spore sorter, gross", 100));
  insert_part(db, set_part(1024, "Health Meter, fin.", 30));
  insert_part(db, set_part(1989776, "Tractor Beam cowl", 30));
  insert_part(db, set_part(98, "magneto", 11));
  insert_part(db, set_part(50, "manual key sort plucker", 11));
  insert_part(db, set_part(40, "Parts List Catalog Index", 19));
  insert_part(db, set_part(99, "funnel lip, unfinished", 1010));
  insert_part(db, set_part(512, "caterpiller feet, left", 1010));
  insert_part(db, set_part(101, "Mental Health Services", 40));
  insert_part(db, set_part(2, "Gas Ring, Municipal", 18));
  insert_part(db, set_part(30, "System flipper", 80));
  insert_part(db, set_part(35, "Stabilizers, horiz,(pair)", 90));
  insert_part(db, set_part(97, "Sink, heat, fur", 2147483647));
  insert_part(db, set_part(401, "Tension Mount", 10));
}
