#ifndef INVENTORY_MODEL_H
#define INVENTORY_MODEL_H
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define NAME_LEN 25

#ifdef USE_INVENTORY_LIST
  #include "inventory-list.h"
#else
  #include "inventory-array.h"
#endif

void new_db(InventoryDatabase *db);
void destroy_db(InventoryDatabase *db);
int insert_part(InventoryDatabase *db, Part p);
int update_part(InventoryDatabase *db, int part_number, int change);
Part *find_part(InventoryDatabase *db, int part_number);
int validate_record(Part *p);
bool is_in_range(int field_value);
void load(InventoryDatabase *db);
void iterate(InventoryDatabase *db, void (*op)(Part *p));
#endif
