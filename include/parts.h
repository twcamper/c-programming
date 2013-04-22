#ifndef PARTS_H
#define PARTS_H
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "part.h"
#include "error.h"

#define NAME_LEN 25
typedef struct parts_type *Parts;

Parts new_db();
void destroy_db(Parts);
int insert_part(Parts, Part);
int delete_part(Parts, PartNumber);
Part find_part(Parts, PartNumber part_number);
void load(Parts);
int dump(char *, Parts);
Parts restore(char *);
void iterate(Parts, void (*op)(Part));
size_t size(Parts);
#endif
