#ifndef INVENTORY_VIEW_H
#define INVENTORY_VIEW_H

#include <stdio.h>
#include "readline.h"
#include "inventory-model.h"

void insert(InventoryDatabase *db);
void search(InventoryDatabase *db);
void update(InventoryDatabase *db);
void print(InventoryDatabase *db);
#endif
