#ifndef INVENTORY_VIEW_H
#define INVENTORY_VIEW_H

#include <stdio.h>
#include "readline.h"
#include "inventory-model.h"

void insert(Parts *db);
void search(Parts *db);
void update(Parts *db);
void print(Parts *db);
#endif
