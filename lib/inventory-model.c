#include "inventory-model.h"

void new_db(Parts *db)
{
  db->count = 0;
  db->requested_row_allocation = INITIAL_SIZE;
  db->rows = malloc(db->requested_row_allocation * sizeof(Part));

  if (db->rows == NULL) {
    fprintf(stderr, "Memory allocation failed: %s:%d (%s)\n", __FILE__, __LINE__, __func__);
    exit(EXIT_FAILURE);
  }
}
void destroy_db(Parts *db)
{
  free(db->rows);
  db->rows = NULL;
  db->count = 0;
}
int resize_db_17_1(Parts *db)
{
  db->requested_row_allocation *= 2;
  Part *temp = realloc(db->rows, db->requested_row_allocation * sizeof(Part));
  if (temp == NULL)
    return -1;

  db->rows = temp;
  return 0;
}
int insert_part(Parts *db, Part p)
{
  int i, j;

  if (db->count == (int)db->requested_row_allocation)
    if ((resize_db_17_1(db) != 0)) {
      return -1;
    }
  /* find position to insert new record */
  for (i = 0; db->rows[i].number <= p.number && i < db->count; i++)
    if (db->rows[i].number == p.number)
      return -2;  /* duplicate record */

  if (validate_record(&p) != 0)
    return -3;

  p.name[NAME_LEN] = '\0';  /* terminate string field, no matter what */
  /* shift remaining records down by 1 */
  for (j = db->count; j > i; j--)
    db->rows[j] = db->rows[j-1];
  /* insert our new record in the newly vacant hole */
  db->rows[i] = p;
  db->count++;
  return 0;
}
int update_part(Parts *db, int number, int change)
{
  int new_value;
  Part *p;
  if (!(p = find_part(db, number)))
    return -1;

  new_value = p->on_hand + change;
  if (!is_in_range(new_value))
    return -2;

  p->on_hand = new_value;
  return 0;
}
/**********************************************************
 * find_part: Looks up a part number in the inventory     *
 *            array. Returns the array index if the part  *
 *            number is found; otherwise, returns -1.     *
 **********************************************************/
Part *find_part(Parts *db, int part_number)
{
  int i;
  for (i = 0; i < db->count; i++)
    if (db->rows[i].number == part_number)
      return &db->rows[i];
  return NULL;
}
int validate_record(Part *p)
{  
  if (is_in_range(p->number) && is_in_range(p->on_hand))
    return 0;
  return -1;
}
bool is_in_range(int field_value)
{
  if (field_value < 0 || field_value > INT_MAX)
    return false;

  return true;
}
void iterate(Parts *db, void (*op)(Part *p))
{
  for (int i = 0; i < db->count; i++)
    op(&db->rows[i]);
}
void load(Parts *db)
{
  insert_part(db, (Part) {212, "Named Part, unlabled", 1});
  insert_part(db, (Part) {12, "Flex Wing Grooming Mower", 19});
  insert_part(db, (Part) {400, "Grommet", 18});
  insert_part(db, (Part) {1, "Fern Spore sorter, gross", 100});
  insert_part(db, (Part) {1024, "Health Meter, fin.", 30});
  insert_part(db, (Part) {1989776, "Tractor Beam cowl", 30});
  insert_part(db, (Part) {98, "magneto", 11});
  insert_part(db, (Part) {50, "manual key sort plucker", 11});
  insert_part(db, (Part) {40, "Parts List Catalog Index", 19});
  insert_part(db, (Part) {99, "funnel lip, unfinished", 1010});
  insert_part(db, (Part) {512, "caterpiller feet, left", 1010});
  insert_part(db, (Part) {101, "Mental Health Services", 40});
  insert_part(db, (Part) {2, "Gas Ring, Municipal", 18});
  insert_part(db, (Part) {30, "System flipper", 80});
  insert_part(db, (Part) {35, "Stabilizers, horiz,(pair)", 90});
  insert_part(db, (Part) {97, "Sink, heat, fur", 2147483647});
  insert_part(db, (Part) {401, "Tension Mount", 10});
}
