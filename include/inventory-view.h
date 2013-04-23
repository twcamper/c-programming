#ifndef INVENTORY_VIEW_H
#define INVENTORY_VIEW_H

#include <stdio.h>
#include "readline.h"
#include "parts.h"

void insert(Parts db);
void erase(Parts db);
void search(Parts db);
void update(Parts db);
void print(Parts db);
Parts prompt_for_db();
#endif
