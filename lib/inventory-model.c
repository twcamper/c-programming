#include "inventory-model.h"

void new_db(InventoryDatabase *db)
{
  db->count = 0;
}
int db_size(InventoryDatabase *db)
{
  return (int) (sizeof(db->rows) / sizeof(db->rows[0]));
}
int insert_part(InventoryDatabase *db, Part p)
{
  if (db->count == MAX_PARTS)
    return -1;
  if (find_part(db, p.number) >= 0)
    return -2;
  if (validate_record(&p) != 0)
    return -3;

  p.name[NAME_LEN] = '\0';
  db->rows[db->count] = p;
  db->count++;
  return 0;
}
int update_part(InventoryDatabase *db, int part_number, int change)
{
  int row, new_value;
  if ((row = find_part(db, part_number)) != 0)
    return -1;

  new_value = db->rows[row].on_hand + change;
  if (!is_in_range(new_value))
    return -2;

  db->rows[row].on_hand = new_value;
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
