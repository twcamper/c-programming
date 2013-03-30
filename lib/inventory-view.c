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
  PartNumber n;
  PartQuantity q;
  char name[NAME_LEN+1];

  printf("Enter part number: ");
  if (read_int(&n) != 0) {
    printf("Invalid part number\n");
    return;
  }
  if (find_part(db, n)) {
    printf("Part already exists.\n");
    return;
  }

  printf("Enter part name: ");
  read_line(name, NAME_LEN);

  printf("Enter quantity on hand: ");
  if (read_int(&q) != 0) {
    printf("Invalid quantity.\n");
    return;
  }

  Part p = set_part(n, name, q);
  if (!p) {
    printf("Record rejected: invalid number.\n");
    return;
  }

  if (insert_part(db,p) != 0) {
    destroy_part(p);
    printf("Memory allocation error.\n");
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
  PartNumber number = 0;
  Part p;

  printf("Enter part number: ");
  if (read_int(&number) != 0) {
    printf("Invalid part number.\n");
    return;
  }
  if ((p = find_part(db, number))) {
    printf("Part name: %s\n", get_part_name(p));
    printf("Quantity on hand: %d\n", get_part_on_hand(p));
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
  PartNumber number;
  PartQuantity change;
  number = change = 0;

  printf("Enter part number: ");
  if (read_int(&number) != 0) {
    printf("Invalid part number.\n");
    return;
  }

  Part p;
  if ((p = find_part(db, number))) {
    printf("Enter change in quantity on hand: ");
    if (read_int(&change) != 0) {
      printf("Invalid quantity.\n");
      return;
    }
    if (update_part(db, number, change) != 0) {
      printf("Invalid new quantity: %d + %d\n", get_part_on_hand(p), change);
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
void print_line(Part p)
{
  printf("%7d       %-25s%11d\n", get_part_number(p), get_part_name(p), get_part_on_hand(p));
}
void print(Parts db)
{
  printf("Part Number   Part Name                   Quantity on Hand\n");
  iterate(db, print_line);
}
