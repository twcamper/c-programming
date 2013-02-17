#include <stdio.h>
#include <stdbool.h>

/*
The following if statement is unnecessarily complicated.
Simplify it as much as possible.

if (age >= 13)
  if (age <= 19)
    teenager = true;
  else
    teenager = false;
else if (age < 13)
  teenager = false;
*/
void test(int age)
{
  printf("Age %d: teenager? %d\n", age, (age > 12 && age < 20) ? true : false);
}
int main(void)
{
  test(0);
  test(1);
  test(12);
  test(13);
  test(19);
  test(20);
  test(101);
  return 0;
}
