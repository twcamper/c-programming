#ifndef INVENTORY_LIST_H
#define INVENTORY_LIST_H

typedef struct Part {
  int number;
  char name[NAME_LEN+1];
  int on_hand;
  struct Part *next;
} Part;
typedef Part InventoryDatabase;

#endif
