#include "inventory-view.h"
#include <monetary.h>
#include <locale.h>

static int enter_part_number(PartNumber *n)
{
  printf("Enter part number: ");
  if (read_int(n) != 0) {
    printf("Invalid part number.\n");
    return -1;
  }

  return 0;
}
/* locale needed for currency formatting */
void init_locale(void)
{
  setlocale(LC_ALL, "en_US");
}
static char * dollars(Part p)
{
  static char s[16];
  strfmon(s, sizeof(s) - 1, "%n",  (double)(get_part_price(p) / 100.00));

  return s;
}

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
  PartPrice cents;
  char name[NAME_LEN+1];

  if (enter_part_number(&n) != 0)
    return;

  if (find_part(db, n)) {
    printf("Part already exists.\n");
    return;
  }

  printf("Enter part name: ");
  read_line(name, NAME_LEN);

  printf("Enter unit price: ");
  if (read_dollars_write_cents(&cents) != 0) {
    printf("Invalid dollar amount.\n");
    return;
  }

  printf("Enter quantity on hand: ");
  if (read_int(&q) != 0) {
    printf("Invalid quantity.\n");
    return;
  }

  Part p = set_part(n, name, q, cents);
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

  if (enter_part_number(&number) != 0)
    return;

  if ((p = find_part(db, number))) {
    printf("Part name: %s\n", get_part_name(p));
    printf("Quantity on hand: %d\n", get_part_on_hand(p));
    printf("Unit price: %s\n", dollars(p));
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
  PartPrice price;
  number = change = price = 0;

  if (enter_part_number(&number) != 0)
    return;

  Part p;
  if ((p = find_part(db, number))) {
    if (yes("\tUpdate quantity on hand? ")) {
      printf("\t\tChange in quantity: ");
      if (read_int(&change) != 0) {
        printf("\t\tInvalid quantity.\n");
        return;
      }
      if (!change_part_on_hand(p, change)) {
        printf("\t\tNew quantity invalid: %d + %d\n", get_part_on_hand(p), change);
        return;
      }
    }
    if (yes("\tUpdate price? ")) {
      printf("\t\tprice: ");
      if (read_dollars_write_cents(&price) != 0) {
        printf("\t\tInvalid price.\n");
        return;
      }
      if (!set_part_price(p, price)) {
        printf("\t\tInvalid price.\n");
        return;
      }
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
static void print_line(Part p)
{
  printf("%-11d       %-25s   %-11d       %-s\n",
         get_part_number(p),
         get_part_name(p),
         get_part_on_hand(p),
         dollars(p));
}
void print(Parts db)
{
  printf("Part Number       Part Name                   Quantity on Hand  Unit Price\n");
  iterate(db, print_line);
}
void erase(Parts db)
{
  PartNumber n;

  if (enter_part_number(&n) != 0)
    return;

  if (delete_part(db, n) != 0) {
    printf("Part not found.\n");
    return;
  }
}
Parts prompt_for_db()
{
  int s;
  printf("Enter database size: ");
  if (read_int(&s) != 0) {
    printf("Invalid size.\n");
    exit(EXIT_FAILURE);
  }

  Parts db = new_db((size_t)s);
  load(db);
  return db;
}
