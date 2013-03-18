#include "inventory-view.h"


/**********************************************************
 * insert: Prompts the user for information about a new   *
 *         part and then inserts the part into the        *
 *         database. Prints an error message and returns  *
 *         prematurely if the part already exists or the  *
 *         database is full.                              *
 **********************************************************/
void insert(InventoryDatabase *db)
{
  Part p = {0, "", 0};

  if (db->count == MAX_PARTS) {
    printf("Database is full; can't add more parts.\n");
    return;
  }

  printf("Enter part number: ");
  if (read_int(&(p.number)) != 0) {
    printf("Invalid part number\n");
    return;
  }
  if (find_part(db, p.number) >= 0) {
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

  if (insert_part(db,p) != 0) {
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
void search(InventoryDatabase *db)
{
  int i, number = 0;

  printf("Enter part number: ");
  if (read_int(&number) != 0) {
    printf("Invalid part number.\n");
    return;
  }
  i = find_part(db, number);
  if (i >= 0) {
    printf("Part name: %s\n", db->rows[i].name);
    printf("Quantity on hand: %d\n", db->rows[i].on_hand);
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
void update(InventoryDatabase *db)
{
  int row, number, change;
  number = change = 0;

  printf("Enter part number: ");
  if (read_int(&number) != 0) {
    printf("Invalid part number.\n");
    return;
  }

  row = find_part(db, number);
  if (row >= 0) {
    printf("Enter change in quantity on hand: ");
    if (read_int(&change) != 0) {
      printf("Invalid quantity.\n");
      return;
    }
    if (update_part(db, row, change) != 0) {
      printf("Invalid new quantity: %d + %d\n", db->rows[row].on_hand, change);
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
void print(InventoryDatabase *db)
{
  int i;

  printf("Part Number   Part Name                  "
         "Quantity on Hand\n");
  for (i = 0; i < db->count; i++)
    printf("%7d       %-25s%11d\n", db->rows[i].number,
           db->rows[i].name, db->rows[i].on_hand);
}
