#include "parts.h"
#include "test_runner.h"
#include <assert.h>

int new_db_test(void)
{
  Parts db = new_db();

  _assert(size(db) == 0);
  destroy_db(db);

  return 0;
}
int insert_part_success_test(void)
{
  Parts db = new_db();

  _assert(size(db) == 0);

  int rc = insert_part(db, set_part(88, "Short Name", 200, 0));
  _assert(rc == 0);
  _assert(size(db) == 1);
  Part p = find_part(db, 88);
  _assert(get_part_number(p) == 88);
  _assert(strcmp(get_part_name(p), "Short Name") == 0);
  _assert(get_part_on_hand(p) == 200);
  destroy_db(db);

  return 0;
}
void assert_for_order_test__(Part p)
{
  static int count = 0;
  switch(count) {
    case 0:
      assert(get_part_number(p) == 86);
      break;
    case 1:
      assert(get_part_number(p) == 87);
      break;
    case 2:
      assert(get_part_number(p) == 88);
      break;
  }
  count++;
}
int insert_part_maintains_order_test(void)
{
  Parts db = new_db();

  insert_part(db, set_part(88, "Short Name", 200, 0));
  insert_part(db, set_part(86, "Short Hair", 10, 0));
  insert_part(db, set_part(87, "Short Sales", 1, 0));

  iterate(db, assert_for_order_test__);
  destroy_db(db);

  return 0;
}
int find_part_test(void)
{
  Parts db = new_db();

  insert_part(db, set_part(88, "Short Name", 200, 0));
  insert_part(db, set_part(212, "Other Name", 2, 0));

  _assert(get_part_number(find_part(db, 212)) == 212);
  _assert(get_part_number(find_part(db, 88)) == 88);
  _assert(find_part(db, 10) == NULL);

  destroy_db(db);

  return 0;
}
int insert_part_fail_non_unique_test(void)
{
  Parts db = new_db();
  int rc = 0; 

  insert_part(db, set_part(88, "Short Name", 200, 0));
  Part p = set_part(88, "Other Name", 2, 0);
  rc = insert_part(db, p);
  _assert(rc == -2);
  _assert(size(db) == 1);
  destroy_part(p);

  p = find_part(db, 88);
  _assert(get_part_number(p) == 88);
  _assert(strcmp(get_part_name(p), "Short Name") == 0);
  _assert(get_part_on_hand(p) == 200);

  destroy_db(db);

  return 0;
}
int insert_part_fail_bad_part_test(void)
{
  Parts db = new_db();
  Part p = set_part(-1, "", -1, 0);

  _assert(insert_part(db, p) != 0);

  destroy_db(db);
  return 0;
}

void mutate_for_iterate_test__(Part p)
{
  set_part_on_hand(p, get_part_on_hand(p) + 1);
}
int iterate_test(void)
{
  Parts db = new_db();

  insert_part(db, set_part(88, "KNOBS", 1, 0));
  insert_part(db, set_part(20, "Noodles", 1, 0));
  insert_part(db, set_part(21, "Nertz", 1, 0));
  _assert(size(db) == 3);

  iterate(db, mutate_for_iterate_test__);
  _assert(get_part_on_hand(find_part(db, 88)) == 2);
  _assert(get_part_on_hand(find_part(db, 20)) == 2);
  _assert(get_part_on_hand(find_part(db, 21)) == 2);
  _assert(size(db) == 3);

  insert_part(db, set_part(122, "None", 1, 0));
  iterate(db, mutate_for_iterate_test__);
  _assert(get_part_on_hand(find_part(db, 88)) == 3);
  _assert(get_part_on_hand(find_part(db, 20)) == 3);
  _assert(get_part_on_hand(find_part(db, 21)) == 3);
  _assert(get_part_on_hand(find_part(db, 122)) == 2);

  destroy_db(db);

  return 0;
}

void assert_for_delete_test__(Part p)
{
  static int count = 0;
  switch(count) {
    case 0:
      assert(get_part_number(p) == 4);
      break;
    case 1:
      assert(get_part_number(p) == 400);
      break;
    case 2:
      assert(get_part_number(p) == 401);
      break;
  }
  count++;
}
int delete_part_test(void)
{
  Parts db = new_db();
  insert_part(db, set_part(4, "first", 1, 0));
  insert_part(db, set_part(40, "second", 1, 0));
  insert_part(db, set_part(400, "third", 1, 0));
  insert_part(db, set_part(401, "last", 1, 0));

  _assert(size(db) == 4);
  _assert(delete_part(db, 40) == 0);
  _assert(size(db) == 3);
  _assert(delete_part(db, 40) != 0);
  _assert(size(db) == 3);

  iterate(db, assert_for_delete_test__);
  _assert(delete_part(db, 4) == 0);
  _assert(size(db) == 2);
  _assert(delete_part(db, 401) == 0);
  _assert(size(db) == 1);

  destroy_db(db);

  return 0;
}
int all_tests(void)
{
  _run(new_db_test);
  _run(insert_part_success_test);
  _run(insert_part_fail_bad_part_test);
  _run(insert_part_fail_non_unique_test);
  _run(insert_part_maintains_order_test);
  _run(find_part_test);
  _run(delete_part_test);
  _run(iterate_test);
  return 0;
}
