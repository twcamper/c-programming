#include <string.h>
#include "inventory-model.h"
#include "test_runner.h"

int new_db_test(void)
{
  InventoryDatabase db;
  new_db(&db);

  _assert(db.count == 0);
  _assert(sizeof(db.rows[0]) == sizeof(part));
  _assert(db_size(&db) == MAX_PARTS);
  return 0;
}
int insert_part_success_test(void)
{
  InventoryDatabase db;
  new_db(&db);
   
  _assert(db.count == 0);

  int rc = insert_part(&db, (part) {88, "Short Name", 200});
  _assert(rc == 0);
  _assert(db.count == 1);
  _assert(db.rows[0].number == 88);
  _assert(strcmp(db.rows[0].name, "Short Name") == 0);
  _assert(db.rows[0].on_hand == 200);
  return 0;
}
int find_part_test(void)
{
  InventoryDatabase db;
  new_db(&db);

  insert_part(&db, (part) {88, "Short Name", 200});
  insert_part(&db, (part) {212, "Other Name", 2});

  _assert(find_part(&db, 212) == 1);
  _assert(find_part(&db, 88) == 0);
  _assert(find_part(&db, 10) == -1);

  return 0;
}
int insert_part_fail_non_unique_test(void)
{
  InventoryDatabase db;
  new_db(&db);
  int rc = 0; 

  insert_part(&db, (part) {88, "Short Name", 200});
  rc = insert_part(&db, (part) {88, "Other Name", 2});
  _assert(rc == -2);
  _assert(db.count == 1);
  _assert(db.rows[0].number == 88);
  _assert(strcmp(db.rows[0].name, "Short Name") == 0);
  _assert(db.rows[0].on_hand == 200);

  return 0;
}
int insert_part_fail_max_records_test(void)
{
  InventoryDatabase db;
  new_db(&db);
  int i, rc = 0; 
  for (i = 0; i < MAX_PARTS; i++)
    rc = insert_part(&db, (part) {i, "name", 10});
  
  _assert(rc == 0);
  _assert(db.count == MAX_PARTS);
   
  rc = insert_part(&db, (part) {312, "unique name", 1020});
  _assert(rc == -1);
  _assert(db.count == MAX_PARTS);
  _assert(find_part(&db, 312) == -1);

  return 0;
}
int all_tests(void)
{
  _run(new_db_test);
  _run(insert_part_success_test);
  _run(find_part_test);
  _run(insert_part_fail_non_unique_test);
  _run(insert_part_fail_max_records_test);
  return 0;
}
