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

  int rc = insert_part(db, set_part(88, "Short Name", 200));
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

  insert_part(db, set_part(88, "Short Name", 200));
  insert_part(db, set_part(86, "Short Hair", 10));
  insert_part(db, set_part(87, "Short Sales", 1));

  iterate(db, assert_for_order_test__);
  destroy_db(db);

  return 0;
}
int find_part_test(void)
{
  Parts db = new_db();

  insert_part(db, set_part(88, "Short Name", 200));
  insert_part(db, set_part(212, "Other Name", 2));

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

  insert_part(db, set_part(88, "Short Name", 200));
  Part p = set_part(88, "Other Name", 2);
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
#define LONG_WORD "Antidisestablishmentariani"
int insert_part_truncates_name_test(void)
{
  Parts db = new_db();

  int rc = insert_part(db, set_part(88, LONG_WORD, 200));

  _assert(rc == 0);
  Part p = find_part(db, 88);
  _assert(get_part_name(p)[NAME_LEN] == '\0');
  _assert(strlen(get_part_name(p)) == NAME_LEN);

  insert_part(db, set_part(89, "Short", 20));
  _assert(strlen(get_part_name(find_part(db, 89))) == 5);

  destroy_db(db);

  return 0;
}
int update_part_success_test(void)
{
  Parts db = new_db();

  insert_part(db, set_part(88, "Ramen, Top", 200));
  _assert(size(db) == 1);
  _assert(update_part(db, 88, 199) == 0);
  Part p = find_part(db, 88);
  _assert(get_part_on_hand(p) == 399);
  _assert(update_part(db, 88, -99) == 0);
  _assert(get_part_on_hand(p) == 300);
  _assert(update_part(db, 88, -300) == 0);
  _assert(get_part_on_hand(p) == 0);
  _assert(size(db) == 1);

  destroy_db(db);

  return 0;
}
int update_part_fail_not_found_test(void)
{

  Parts db = new_db();

  insert_part(db, set_part(88, "Joystick, rotating", 200));
  _assert(size(db) == 1);
  _assert(update_part(db, 89, 199) != 0);
  _assert(update_part(db, 1, 199) != 0);
  _assert(size(db) == 1);
  destroy_db(db);

  return 0;
}
int update_part_fail_invalid_test(void)
{

  Parts db = new_db();

  insert_part(db, set_part(88, "Mercy!", 20));
  _assert(size(db) == 1);
  _assert(update_part(db, 88, -21) != 0);
  Part p = find_part(db, 88);
  _assert(get_part_on_hand(p) == 20);
  _assert(update_part(db, 88, INT_MAX) != 0);
  _assert(get_part_on_hand(p) == 20);
  _assert(size(db) == 1);
  destroy_db(db);

  return 0;
}

void mutate_for_iterate_test__(Part p)
{
  set_part_on_hand(p, get_part_on_hand(p) + 1);
}
void assert_for_iterate_test__(Part p) { assert(get_part_on_hand(p) == 2); }
void assert2_for_iterate_test__(Part p)
{
  static int count = 0;
  if (count == 3)
    assert(get_part_on_hand(p) == 2);
  else
    assert(get_part_on_hand(p) == 3);

  count++;
}
int iterate_test(void)
{
  Parts db = new_db();

  insert_part(db, set_part(88, "KNOBS", 1));
  insert_part(db, set_part(20, "Noodles", 1));
  insert_part(db, set_part(21, "Nertz", 1));
  _assert(size(db) == 3);

  iterate(db, mutate_for_iterate_test__);
  iterate(db, assert_for_iterate_test__);
  _assert(size(db) == 3);

  insert_part(db, set_part(122, "None", 1));
  iterate(db, mutate_for_iterate_test__);
  iterate(db, assert2_for_iterate_test__);

  destroy_db(db);

  return 0;
}

int all_tests(void)
{
  _run(new_db_test);
  _run(insert_part_success_test);
  _run(insert_part_truncates_name_test);
  _run(insert_part_fail_non_unique_test);
  _run(insert_part_maintains_order_test);
  _run(find_part_test);
  _run(update_part_success_test);
  _run(update_part_fail_not_found_test);
  _run(update_part_fail_invalid_test);
  _run(iterate_test);
  return 0;
}
