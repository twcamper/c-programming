#ifndef PART_H
#define PART_H

#include <limits.h>
#include <string.h>
#include <stdbool.h>
#define NAME_LEN 25

typedef struct part_type *Part;

Part new_part(void);
Part set_part(int, char *, int);
bool set_part_number(Part, int);
void set_part_name(Part, char *);
bool set_part_on_hand(Part, int);
int get_part_number(Part);
char * get_part_name(Part);
int get_part_on_hand(Part);
void destroy_part(Part);

#endif
