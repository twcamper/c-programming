#include "inventory-view.h"

static int enter_part_number(PartNumber *n)
{
  printf("Enter part number: ");
  if (read_int(n) != 0) {
    printf("Invalid part number.\n");
    return -1;
  }

  return 0;
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
static int prompt_for_page(void)
{
  PartNumber n;
  char response[2];
  while (read_line(response, 2) != '\n') {
    switch (tolower(response[0])) {
      case 'q':
        return -2;
      case 's':
        if (enter_part_number(&n) != 0)
          break;
        return n;
      case 'e':
        return -3;
      default:
        return -1;
    }
  }
  return -1;
}
void print(Parts db)
{
  printf("Part Number       Part Name                                            Quantity on Hand  Unit Price\n");
  iterate_by_page(db, 40, print_part, prompt_for_page);
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
Parts load_db(Parts old_db)
{
  char line[1024];
  Parts new_db;

  printf("Enter a data file name: ");
  if (read_line(line, (int)(sizeof(line) / sizeof(line[0])))) {
    if ((new_db = load_parts(line)) == NULL) {
      if (is_file_name_error(errno)) {
        errno = 0;
        return old_db;
      } else {
        destroy_db(old_db);
        exit(EXIT_FAILURE);
      }
    }
    destroy_db(old_db);
    return new_db;
  } else {
    printf("Invalid input. (%s)\n", line);
    return old_db;
  }
}
Parts init_db(char *file)
{
  Parts db;
  if (strlen(file)) {
    if ((db = load_parts(file)) == NULL) exit(EXIT_FAILURE);
    return db;
  } else {
    return new_db(20);
  }
}
void save_db(Parts db)
{
  char line[1024];
  printf("Enter a data file name: ");
  if (read_line(line, (int)(sizeof(line) / sizeof(line[0])))) {
    if ((dump(line, db)) != 0) {
      if (is_file_name_error(errno)) {
        errno = 0;
        return;
      } else {
        exit(EXIT_FAILURE);
      }
    }
  } else {
    printf("Invalid input. (%s)\n", line);
    return;
  }
}
