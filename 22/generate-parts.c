#include <time.h>
#include <stdlib.h>
#include "parts.h"
#include "part.h"
#include "inventory-view.h"
#include "tokenize.h"

static void print_line(Part p)
{
  printf("%-11d       %-25s   %-11d       %-d\n",
         get_part_number(p),
         get_part_name(p),
         get_part_on_hand(p),
         get_part_price(p));
}
size_t jagged_sequence(size_t previous)
{
  return previous + (rand() % 13);
}
char *noun(void)
{

}
char *adjective(void)
{
}
char *random_part_name(void)
{
  static char name[NAME_LEN + 1]; /* static so we can return it */
  static FILE *nouns;
  static FILE *adjectives;

  sprintf(name, "%s, %s %s", noun(), adjective(), adjective());

  return name;
}
PartQuantity random_part_quantity(void)
{
  return rand() % INT_MAX;
}

PartPrice random_part_price(void)
{
  return rand() % INT_MAX;
}

int main(int argc, char *argv[])
{
  if (argc != 3)
    invocation_error(argv[0], "[output file] [size]");

  char *output_file = argv[1];
  size_t records = atol(argv[2]);
  size_t i, part_number;

  Parts db = new_db(records);

  srand((unsigned int) time(NULL));
  for (part_number = 0, i = 0; i < records; i++) {
    part_number = jagged_sequence(part_number);
    insert_part(db, set_part(part_number,
          random_part_name(),
          random_part_quantity(),
          random_part_price()));
  }

  if (dump(output_file, db) != 0) {
    destroy_db(db);
    exit_error(errno, argv[0], output_file);
  }
  destroy_db(db);

  return 0;
}
