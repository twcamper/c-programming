#ifndef PART_TYPE_H
#define PART_TYPE_H
#include "part.h"
struct part_type
{
  PartNumber number;
  char name[NAME_LEN+1];
  PartQuantity on_hand;
  PartPrice price;
};
#endif
