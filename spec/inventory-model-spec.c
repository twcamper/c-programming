#include <string.h>
#include "inventory-model.h"
#include "test_runner.h"

#define INITIAL_SIZE 100

struct parts_type {
  int count; 
  Part *rows;
  size_t requested_row_allocation;
};
void print_record(Part p)
{
  printf("number: %d\nname: %s length:%d\non_hand: %d\n", p.number, p.name, (int)strlen(p.name), p.on_hand);
}
int new_db_test(void)
{
  Parts db = new_db(INITIAL_SIZE);

  _assert(db->count == 0);
  _assert(sizeof(db->rows[0]) == sizeof(Part));
  _assert(sizeof(db->rows[INITIAL_SIZE - 1]) == sizeof(Part));
  _assert(db->requested_row_allocation == INITIAL_SIZE);
  destroy_db(db);

  return 0;
}
int insert_part_success_test(void)
{
  Parts db = new_db(INITIAL_SIZE);

  _assert(db->count == 0);

  int rc = insert_part(db, (Part) {88, "Short Name", 200});
  _assert(rc == 0);
  _assert(db->count == 1);
  _assert(db->rows[0].number == 88);
  _assert(strcmp(db->rows[0].name, "Short Name") == 0);
  _assert(db->rows[0].on_hand == 200);
  destroy_db(db);

  return 0;
}
int insert_part_maintains_order_test(void)
{
  Parts db = new_db(INITIAL_SIZE);

  insert_part(db, (Part) {88, "Short Name", 200});
  insert_part(db, (Part) {86, "Short Hair", 10});
  insert_part(db, (Part) {87, "Short Sales", 1});

  _assert(db->rows[0].number == 86);
  _assert(db->rows[1].number == 87);
  _assert(db->rows[2].number == 88);
  destroy_db(db);

  return 0;
}
int find_part_test(void)
{
  Parts db = new_db(INITIAL_SIZE);

  insert_part(db, (Part) {88, "Short Name", 200});
  insert_part(db, (Part) {212, "Other Name", 2});

  _assert(find_part(db, 212)->number == 212);
  _assert(find_part(db, 88)->number == 88);
  _assert(find_part(db, 10) == NULL);

  destroy_db(db);

  return 0;
}
int insert_part_fail_non_unique_test(void)
{
  Parts db = new_db(INITIAL_SIZE);
  int rc = 0; 

  insert_part(db, (Part) {88, "Short Name", 200});
  rc = insert_part(db, (Part) {88, "Other Name", 2});
  _assert(rc == -2);
  _assert(db->count == 1);
  _assert(db->rows[0].number == 88);
  _assert(strcmp(db->rows[0].name, "Short Name") == 0);
  _assert(db->rows[0].on_hand == 200);

  destroy_db(db);

  return 0;
}
int insert_part_resize_test(void)
{
  Parts db = new_db(INITIAL_SIZE);
  int i, rc = 0;
  for (i = 0; i < INITIAL_SIZE - 1; i++)
    insert_part(db, (Part) {i, "name", 10});

  rc = insert_part(db, (Part) {i, "name", 10});

  _assert(db->requested_row_allocation == INITIAL_SIZE);
  _assert(rc == 0);
  _assert(db->count == INITIAL_SIZE);

  Part *p;
  int part_number = db->count  + 1;
  rc = insert_part(db, (Part) {part_number, "unique name", 1020});
  _assert(rc == 0);
  _assert(db->requested_row_allocation == INITIAL_SIZE * 2);
  _assert(db->count == INITIAL_SIZE + 1);
  p = find_part(db, part_number);
  _assert(p->number == part_number);
  _assert(strcmp(p->name,"unique name") == 0);
  _assert(p->on_hand == 1020);

  size_t new_size = INITIAL_SIZE * 2;
  for (i = db->count; i < (int)db->requested_row_allocation - 1; i++)
    insert_part(db, (Part) {i+1, "name", 10});

  rc = insert_part(db, (Part) {i+1, "name", 10});

  _assert(db->requested_row_allocation == new_size);
  _assert(rc == 0);
  _assert(db->count == (int)new_size);

  part_number = db->count  + 1;
  rc = insert_part(db, (Part) {part_number, "Fairly unique name", 1021});
  _assert(rc == 0);
  _assert(db->requested_row_allocation == INITIAL_SIZE * 4);
  _assert(db->count == 1 + (int) new_size);
  p = find_part(db, part_number);
  _assert(p->number == part_number);
  _assert(strcmp(p->name,"Fairly unique name") == 0);
  _assert(p->on_hand == 1021);

  destroy_db(db);

  return 0;
}
#define LONG_WORD "Antidisestablishmentariani"
int insert_part_truncates_name_test(void)
{
  Parts db = new_db(INITIAL_SIZE);

  int rc = insert_part(db, (Part) {88, LONG_WORD, 200});

  _assert(rc == 0);
  _assert(db->rows[0].name[NAME_LEN] == '\0');
  _assert(strlen(db->rows[0].name) == NAME_LEN);

  insert_part(db, (Part) {89, "Short", 20});
  _assert(strlen(db->rows[1].name) == 5);

  destroy_db(db);

  return 0;
}
int update_part_success_test(void)
{
  Parts db = new_db(INITIAL_SIZE);

  insert_part(db, (Part) {88, "Ramen, Top", 200});
  _assert(db->count == 1);
  _assert(update_part(db, 88, 199) == 0);
  _assert(db->rows[0].on_hand == 399);
  _assert(update_part(db, 88, -99) == 0);
  _assert(db->rows[0].on_hand == 300);
  _assert(update_part(db, 88, -300) == 0);
  _assert(db->rows[0].on_hand == 0);
  _assert(db->count == 1);

  destroy_db(db);

  return 0;
}
int update_part_fail_not_found_test(void)
{

  Parts db = new_db(INITIAL_SIZE);

  insert_part(db, (Part) {88, "Joystick, rotating", 200});
  _assert(db->count == 1);
  _assert(update_part(db, 89, 199) != 0);
  _assert(update_part(db, 1, 199) != 0);
  _assert(db->count == 1);
  destroy_db(db);

  return 0;
}
int update_part_fail_invalid_test(void)
{

  Parts db = new_db(INITIAL_SIZE);

  insert_part(db, (Part) {88, "Mercy!", 20});
  _assert(db->count == 1);
  _assert(update_part(db, 88, -21) != 0);
  _assert(db->rows[0].on_hand == 20);
  _assert(update_part(db, 88, INT_MAX) != 0);
  _assert(db->rows[0].on_hand == 20);
  _assert(db->count == 1);
  destroy_db(db);

  return 0;
}

void for_iterate_test__(Part *p) { p->on_hand++; }
int iterate_test(void)
{
  Parts db = new_db(INITIAL_SIZE);

  insert_part(db, (Part) {88, "KNOBS", 1});
  insert_part(db, (Part) {20, "Noodles", 1});
  insert_part(db, (Part) {21, "Nertz", 1});
  _assert(db->count == 3);

  iterate(db, for_iterate_test__);
  _assert(db->rows[0].on_hand == 2);
  _assert(db->rows[1].on_hand == 2);
  _assert(db->rows[2].on_hand == 2);
  _assert(db->count == 3);

  insert_part(db, (Part) {122, "None", 1});
  iterate(db, for_iterate_test__);
  _assert(db->rows[0].on_hand == 3);
  _assert(db->rows[1].on_hand == 3);
  _assert(db->rows[2].on_hand == 3);
  _assert(db->rows[3].on_hand == 2);

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
  _run(insert_part_resize_test);
  _run(update_part_success_test);
  _run(update_part_fail_not_found_test);
  _run(update_part_fail_invalid_test);
  _run(iterate_test);
  return 0;
}
