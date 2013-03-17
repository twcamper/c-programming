#include "inventory-model.h"

void new_db(InventoryDatabase *db)
{
  db->count = 0;
}
int db_size(InventoryDatabase *db)
{
  return (int) (sizeof(db->rows) / sizeof(db->rows[0]));
}
int insert_part(InventoryDatabase *db, part p)
{
  if (db->count == MAX_PARTS)
    return -1;
  if (find_part(db, p.number) >= 0)
    return -2;

  db->rows[db->count] = p;
  db->count++;
  return 0;
}
int find_part(InventoryDatabase *db, int part_number)
{
  int i;
  for (i = 0; i < db->count; i++)
    if (db->rows[i].number == part_number)
      return i;
  return -1;
}
