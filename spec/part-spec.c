#include "part.h"
#include "test_runner.h"

int new_part_test(void)
{
  Part p = new_part();

  _assert(get_part_number(p) == 0);
  _assert(strcmp(get_part_name(p), "") == 0);
  _assert(get_part_on_hand(p) == 0);

  destroy_part(p);

  return 0;
}

int set_part_test(void)
{
  Part p = set_part(33, "It's a Part!", 1, 100);
  _assert(get_part_number(p) == 33);
  _assert(strcmp(get_part_name(p), "It's a Part!") == 0);
  _assert(get_part_on_hand(p) == 1);
  _assert(get_part_price(p) == 100);

  destroy_part(p);
  return 0;
}
int set_part_invalid_number_test(void)
{
  _assert(set_part(-1, "", 0, 0) == NULL);
  return 0;
}
int set_part_invalid_on_hand_test(void)
{
  _assert(set_part(1, "", -1, 0) == NULL);
  return 0;
}
int set_part_invalid_price_test(void)
{
  _assert(set_part(1, "", 1, -1) == NULL);
  return 0;
}

int set_part_number_test(void)
{
  Part p = new_part();
  _assert(set_part_number(p,  0) == true);
  _assert(get_part_number(p) == 0);
  _assert(set_part_number(p, INT_MAX) == true);
  _assert(get_part_number(p) == INT_MAX);
  _assert(set_part_number(p, -1) == false);
  _assert(set_part_number(p,  INT_MAX + 1) == false);

  destroy_part(p);
  return 0;
}
#define LONG_WORD "123456789012345678901234567890123456789012345678901"
int set_part_name_truncates_test(void)
{
  Part p = new_part();
  set_part_name(p, LONG_WORD);

  _assert(get_part_name(p)[NAME_LEN] == '\0');
  _assert(strlen(get_part_name(p)) == NAME_LEN);

  set_part_name(p, "Short");
  _assert(strlen(get_part_name(p)) == 5);
  _assert(strcmp(get_part_name(p), "Short") == 0);

  destroy_part(p);
  return 0;
}
int set_part_on_hand_test(void)
{
  Part p = new_part();
  _assert(set_part_on_hand(p,  0) == true);
  _assert(get_part_on_hand(p) == 0);
  _assert(set_part_on_hand(p, INT_MAX) == true);
  _assert(get_part_on_hand(p) == INT_MAX);
  _assert(set_part_on_hand(p, -1) == false);
  _assert(set_part_on_hand(p,  INT_MAX + 1) == false);

  destroy_part(p);

  return 0;
}
int set_part_price_test(void)
{
  Part p = new_part();
  _assert(set_part_price(p,  0) == true);
  _assert(get_part_price(p) == 0);
  _assert(set_part_price(p, INT_MAX) == true);
  _assert(get_part_price(p) == INT_MAX);
  _assert(set_part_price(p, -1) == false);
  _assert(set_part_price(p,  INT_MAX + 1) == false);

  destroy_part(p);
  return 0;
}

int change_part_on_hand_success_test(void)
{
  Part p = set_part(88, "Ramen, Top", 200, 0);
  _assert(change_part_on_hand(p, 199) == true);
  _assert(get_part_on_hand(p) == 399);
  _assert(change_part_on_hand(p, -99) == true);
  _assert(get_part_on_hand(p) == 300);
  _assert(change_part_on_hand(p, -300) == true);
  _assert(get_part_on_hand(p) == 0);

  destroy_part(p);

  return 0;
}
int change_part_on_hand_fail_invalid_test(void)
{
  Part p = set_part(88, "Ramen, Top", 20, 0);
  _assert(change_part_on_hand(p, -21) == false);
  _assert(get_part_on_hand(p) == 20);
  _assert(change_part_on_hand(p, INT_MAX) == false);
  _assert(get_part_on_hand(p) == 20);

  destroy_part(p);

  return 0;
}
int all_tests(void)
{

  _run(new_part_test);
  _run(set_part_test);
  _run(set_part_invalid_number_test);
  _run(set_part_invalid_on_hand_test);
  _run(set_part_number_test);
  _run(set_part_name_truncates_test);
  _run(set_part_on_hand_test);
  _run(change_part_on_hand_success_test);
  _run(change_part_on_hand_fail_invalid_test);
  _run(set_part_price_test);
  _run(set_part_invalid_price_test);
  return 0;
}
