#include "inventory-view.h"


/**********************************************************
 * insert: Prompts the user for information about a new   *
 *         part and then inserts the part into the        *
 *         database. Prints an error message and returns  *
 *         prematurely if the part already exists or the  *
 *         database is full.                              *
 **********************************************************/
void insert(Parts db)
{
  Part p = {0, "", 0};

  printf("Enter part number: ");
  if (read_int(&(p.number)) != 0) {
    printf("Invalid part number\n");
    return;
  }
  if (find_part(db, p.number)) {
    printf("Part already exists.\n");
    return;
  }

  printf("Enter part name: ");
  read_line(p.name, NAME_LEN);

  printf("Enter quantity on hand: ");
  if (read_int(&(p.on_hand)) != 0) {
    printf("Invalid quantity.\n");
    return;
  }

  switch(insert_part(db,p)) {
    case -1:
      printf("Memory allocation error.\n");
      return;
    case -3:
      printf("Record rejected: invalid number.\n");
      return;
  }
}

/**********************************************************
 * search: Prompts the user to enter a part number, then  *
 *         looks up the part in the database. If the part *
 *         exists, prints the name and quantity on hand;  *
 *         if not, prints an error message.               *
 **********************************************************/
void search(Parts db)
{
  int number = 0;
  Part *p;

  printf("Enter part number: ");
  if (read_int(&number) != 0) {
    printf("Invalid part number.\n");
    return;
  }
  if ((p = find_part(db, number))) {
    printf("Part name: %s\n", p->name);
    printf("Quantity on hand: %d\n", p->on_hand);
  } else
    printf("Part not found.\n");
}

/**********************************************************
 * update: Prompts the user to enter a part number.       *
 *         Prints an error message if the part doesn't    *
 *         exist; otherwise, prompts the user to enter    *
 *         change in quantity on hand and updates the     *
 *         database.                                      *
 **********************************************************/
void update(Parts db)
{
  int number, change;
  number = change = 0;

  printf("Enter part number: ");
  if (read_int(&number) != 0) {
    printf("Invalid part number.\n");
    return;
  }

  Part *p;
  if ((p = find_part(db, number))) {
    printf("Enter change in quantity on hand: ");
    if (read_int(&change) != 0) {
      printf("Invalid quantity.\n");
      return;
    }
    if (update_part(db, number, change) != 0) {
      printf("Invalid new quantity: %d + %d\n", p->on_hand, change);
      return;
    }
  } else
    printf("Part not found.\n");
}

/**********************************************************
 * print: Prints a listing of all parts in the database,  *
 *        showing the part number, part name, and         *
 *        quantity on hand. Parts are printed in the      *
 *        order in which they were entered into the       *
 *        database.                                       *
 **********************************************************/
void print_line(Part *p)
{
  printf("%7d       %-25s%11d\n", p->number, p->name, p->on_hand);
}
void print(Parts db)
{
  printf("Part Number   Part Name                   Quantity on Hand\n");
  iterate(db, print_line);
}
