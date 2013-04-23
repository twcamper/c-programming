#ifndef PART_H
#define PART_H

#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <monetary.h>
#include <locale.h>
#define NAME_LEN 50

typedef struct part_type *Part;
typedef int PartNumber;
typedef int PartQuantity;
typedef int PartPrice;

Part new_part(void);
Part set_part(PartNumber, char *, PartQuantity, PartPrice);
bool set_part_number(Part, PartNumber);
void set_part_name(Part, char *);
bool set_part_on_hand(Part, PartQuantity);
bool change_part_on_hand(Part, PartQuantity);
bool set_part_price(Part, PartPrice);
PartNumber get_part_number(Part);
char * get_part_name(Part);
PartQuantity get_part_on_hand(Part);
PartPrice get_part_price(Part);
void destroy_part(Part);
void init_locale(void);
char * dollars(Part);
void print_part(Part);

#endif
