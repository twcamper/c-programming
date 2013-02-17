#include <stdio.h>

int main(void)
{
  int gs1_prefix, group_id, publisher_code, item_number, check_digit;

  printf("Enter ISBN: ");
  scanf("%d-%d-%d-%d-%d", &gs1_prefix, &group_id, &publisher_code, &item_number, &check_digit);

  printf("GS1 prefix: %d\n", gs1_prefix);
  printf("Group Identifier: %d\n", group_id);
  printf("Publisher Code: %d\n", publisher_code);
  printf("Item Number: %d\n", item_number);
  printf("Check Digit: %d\n", check_digit);

  return 0;
}
