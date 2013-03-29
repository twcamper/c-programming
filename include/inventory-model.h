#ifndef INVENTORY_MODEL_H
#define INVENTORY_MODEL_H
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define NAME_LEN 25
#define INITIAL_SIZE 30000

typedef struct Part {
  int number;
  char name[NAME_LEN+1];
  int on_hand;
} Part;

typedef struct InventoryDatabase {
  int count; 
  Part *rows;
  size_t requested_row_allocation;
} InventoryDatabase;

void new_db(InventoryDatabase *db);
void destroy_db(InventoryDatabase *db);
int resize_db_17_1(InventoryDatabase *db);
int insert_part(InventoryDatabase *db, Part p);
int update_part(InventoryDatabase *db, int part_number, int change);
Part *find_part(InventoryDatabase *db, int part_number);
int validate_record(Part *p);
bool is_in_range(int field_value);
void load(InventoryDatabase *db);
void iterate(InventoryDatabase *db, void (*op)(Part *p));
#endif
