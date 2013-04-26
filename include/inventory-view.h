#ifndef INVENTORY_VIEW_H
#define INVENTORY_VIEW_H

#include <stdio.h>
#include "readline.h"
#include "parts.h"

void insert(Parts);
void erase(Parts);
void search(Parts);
void update(Parts);
void print(Parts);
Parts load_db(Parts);
void save_db(Parts);
Parts init_db(char *);
#endif
