#include "parts.h"
#include "test_runner.h"
#define INITIAL_SIZE 30

int insert_part_resize_test(void)
{
  Parts db = new_db();
  size_t i;
  int rc = 0;

  for (i = 0; i < INITIAL_SIZE - 1; i++)
    insert_part(db, set_part(i, "name", 10, 0));

  rc = insert_part(db, set_part(i, "name", 10, 0));

  _assert(rc == 0);
  _assert(size(db) == INITIAL_SIZE);

  Part p;
  int part_number = size(db)  + 1;
  rc = insert_part(db, set_part(part_number, "unique name", 1020, 0));
  _assert(rc == 0);
  _assert(size(db) == INITIAL_SIZE + 1);
  p = find_part(db, part_number);
  _assert(get_part_number(p) == part_number);
  _assert(strcmp(get_part_name(p),"unique name") == 0);
  _assert(get_part_on_hand(p) == 1020);

  size_t new_size = INITIAL_SIZE * 2;
  for (i = size(db); i < (new_size - 1); i++)
    insert_part(db, set_part(i+1, "name", 10, 0));

  rc = insert_part(db, set_part(i+1, "name", 10, 0));

  _assert(rc == 0);
  _assert(size(db) == new_size);

  part_number = size(db)  + 1;
  rc = insert_part(db, set_part(part_number, "Fairly unique name", 1021, 0));
  _assert(rc == 0);
  _assert(size(db) == 1 + new_size);
  p = find_part(db, part_number);
  _assert(get_part_number(p) == part_number);
  _assert(strcmp(get_part_name(p),"Fairly unique name") == 0);
  _assert(get_part_on_hand(p) == 1021);

  destroy_db(db);

  return 0;
}

int all_tests(void)
{
  _run(insert_part_resize_test);
  return 0;
}
