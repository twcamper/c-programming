#ifndef PART_H
#define PART_H

#include <limits.h>
#include <string.h>
#include <stdbool.h>
#define NAME_LEN 25

typedef struct part_type *Part;
typedef int PartNumber;
typedef int PartQuantity;

Part new_part(void);
Part set_part(PartNumber, char *, PartQuantity);
bool set_part_number(Part, PartNumber);
void set_part_name(Part, char *);
bool set_part_on_hand(Part, PartQuantity);
PartNumber get_part_number(Part);
char * get_part_name(Part);
PartQuantity get_part_on_hand(Part);
void destroy_part(Part);

#endif
