#ifndef INVENTORY_ARRAY_H
#define INVENTORY_ARRAY_H

#include <stdio.h>
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

int resize_db_17_1(InventoryDatabase *db);
void sort_on_part_number(InventoryDatabase *db);
#endif
