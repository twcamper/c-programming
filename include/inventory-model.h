#ifndef INVENTORY_MODEL_H
#define INVENTORY_MODEL_H
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_SIZE 30000
#define NAME_LEN 25

typedef struct Part {
  int number;
  char name[NAME_LEN+1];
  int on_hand;
} Part;

typedef struct Parts {
  int count; 
  Part *rows;
  size_t requested_row_allocation;
} Parts;

void new_db(Parts *db);
void destroy_db(Parts *db);
int resize_db_17_1(Parts *db);
int insert_part(Parts *db, Part p);
int update_part(Parts *db, int part_number, int change);
Part *find_part(Parts *db, int part_number);
int validate_record(Part *p);
bool is_in_range(int field_value);
void load(Parts *db);
void iterate(Parts *db, void (*op)(Part *p));
#endif
