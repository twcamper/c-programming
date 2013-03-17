#ifndef INVENTORY_MODEL_H
#define INVENTORY_MODEL_H

#define NAME_LEN 25
#define MAX_PARTS 100

typedef struct part {
  int number;
  char name[NAME_LEN+1];
  int on_hand;
} part;

typedef struct InventoryDatabase {
  int count; 
  part rows[MAX_PARTS];
} InventoryDatabase;

void new_db(InventoryDatabase *db);
int db_size(InventoryDatabase *db);
int insert_part(InventoryDatabase *db, part p);
int find_part(InventoryDatabase *db, int part_number);
#endif
