#ifndef INVENTORY_MODEL_H
#define INVENTORY_MODEL_H
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define NAME_LEN 25

typedef struct Part {
  int number;
  char name[NAME_LEN+1];
  int on_hand;
} Part;

typedef struct parts_type *Parts;

Parts new_db(int);
void destroy_db(Parts);
int insert_part(Parts, Part);
int update_part(Parts, int part_number, int change);
Part *find_part(Parts, int part_number);
int validate_record(Part *p);
void load(Parts);
void iterate(Parts, void (*op)(Part *));
#endif
