#include "inventory-model.h"

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
void load(InventoryDatabase *db)
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
