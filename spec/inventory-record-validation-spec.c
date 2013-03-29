#include "inventory-model.h"
#include "test_runner.h"

int insert_part_fail_invalid_record_test(void)
{

  Parts db;
  new_db(&db);

  int rc = insert_part(&db, (Part) {-1, "n", 200});
  _assert(rc != 0);
  _assert(db.count == 0);
  _assert(db.rows[0].number != -1);

  rc = insert_part(&db, (Part) {1, "n", INT_MAX + 1});
  _assert(rc != 0);
  _assert(db.count == 0);
  return 0;
}
int validate_record_test(void)
{
  _assert(validate_record(&(Part) {0, "N", 0}) == 0);
  _assert(validate_record(&(Part) {INT_MAX, "N", INT_MAX}) == 0);
  _assert(validate_record(&(Part) {-1, "N", 0}) != 0);
  _assert(validate_record(&(Part) {0, "N", -1}) != 0);
  _assert(validate_record(&(Part) {-1, "N", -1}) != 0);
  _assert(validate_record(&(Part) {INT_MAX, "N", INT_MAX + 1}) != 0);
  _assert(validate_record(&(Part) {INT_MAX + 1, "N", INT_MAX + 1}) != 0);
  _assert(validate_record(&(Part) {INT_MAX + 1, "N", INT_MAX}) != 0);
   
  return 0;
}

int all_tests(void)
{

  _run(validate_record_test);
  _run(insert_part_fail_invalid_record_test);
  return 0;
}
