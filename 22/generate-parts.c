#include "parts.h"
#include "inventory-view.h"

static void print_line(Part p)
{
  printf("%-11d       %-25s   %-11d       %-d\n",
         get_part_number(p),
         get_part_name(p),
         get_part_on_hand(p),
         get_part_price(p));
}
int main(int argc, char *argv[])
{
  if (argc != 3)
    invocation_error(argv[0], "[output file] [size]");

  char *output_file = argv[1];
  size_t records = atol(argv[2]);

  Parts db1 = new_db();
  Parts db2;

  load(db1);

  if (dump(output_file, db1) != 0) {
    destroy_db(db1);
    exit_error(errno, argv[0], output_file);
  }
  destroy_db(db1);

  if ((db2 = restore(output_file)) == NULL) {
    exit_error(errno, argv[0], output_file);
  }

  insert_part(db2, set_part(31, "winky, putrescent", 33, 4999));
  iterate(db2, print_line);

  destroy_db(db2);
  return 0;
}
