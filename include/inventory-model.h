#ifndef INVENTORY_MODEL_H
#define INVENTORY_MODEL_H
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define NAME_LEN 25
#define MAX_PARTS 100

typedef struct Part {
  int number;
  char name[NAME_LEN+1];
  int on_hand;
} Part;

typedef struct InventoryDatabase {
  int count; 
  Part rows[MAX_PARTS];
} InventoryDatabase;

void new_db(InventoryDatabase *db);
int db_size(InventoryDatabase *db);
int insert_part(InventoryDatabase *db, Part p);
int update_part(InventoryDatabase *db, int part_number, int change);
Part *find_part(InventoryDatabase *db, int part_number);
int validate_record(Part *p);
bool is_in_range(int field_value);
void load(InventoryDatabase *db);
void sort_on_part_number(InventoryDatabase *db);
void iterate(InventoryDatabase *db, void (*op)(Part *p));
#endif
