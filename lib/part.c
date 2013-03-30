#include <stdlib.h>
#include "error.h"
#include "part.h"

struct part_type
{
  int number;
  char name[NAME_LEN+1];
  int on_hand;
};

Part new_part(void)
{
  Part p = malloc(sizeof(struct part_type));
  if (!p)
    memory_error(__FILE__, __LINE__, __func__);

  return p;
}
Part set_part(int number, char * name, int on_hand)
{
  Part p = new_part();

  if (!( set_part_number(p, number) &&
         set_part_on_hand(p, on_hand) ))
  {
    destroy_part(p);
    return NULL;
  }

  set_part_name(p, name);

  return p;
}
static bool is_in_range(int field_value)
{
  if (field_value < 0 || field_value > INT_MAX)
    return false;

  return true;
}
bool set_part_number(Part p, int number)
{
  if (is_in_range(number)) {
    p->number = number;
    return true;
  }
  return false;
}
void set_part_name(Part p, char *name)
{
  strcpy(p->name,  name);
  p->name[NAME_LEN] = '\0';  /* terminate string field, no matter what */
}
bool set_part_on_hand(Part p, int quantity)
{
  if (is_in_range(quantity)) {
    p->on_hand = quantity;
    return true;
  }
  return false;
}
int get_part_number(Part p)  {return p->number; }
char * get_part_name(Part p) {return p->name; }
int get_part_on_hand(Part p) {return p->on_hand; }
void destroy_part(Part p)
{
  free(p);
}
