#include <stdio.h>

int main(void)
{
  int area_code, exchange, number;
  printf("Enter phone number [(xxx) xxx-xxxx]: ");

  scanf("(%d) %d-%d", &area_code, &exchange, &number);

  printf("You entered %3d.%3d.%4d\n", area_code, exchange, number);
  return 0;
}
