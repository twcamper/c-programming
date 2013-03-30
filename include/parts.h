#ifndef INVENTORY_MODEL_H
#define INVENTORY_MODEL_H
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "part.h"
#include "error.h"

#define NAME_LEN 25
typedef struct parts_type *Parts;

/*
 * TODO:  add erase_part()  (see 17/17.3-inventory.c source)
 *        for both array and list
 *
 *        price field
 *
 *        update price
 */

Parts new_db();
void destroy_db(Parts);
int insert_part(Parts, Part);
int update_part(Parts, PartNumber part_number, PartQuantity change);
Part find_part(Parts, PartNumber part_number);
void load(Parts);
void iterate(Parts, void (*op)(Part));
int size(Parts);
#endif
