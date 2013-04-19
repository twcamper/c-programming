#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
  char *pattern = " #%[0123456789,]";
  char sales_rank[255];

  sscanf(" #123", pattern, &sales_rank);
  assert(strcmp(sales_rank, "123") == 0);

  sscanf(" #999,999,901 ", pattern, &sales_rank);
  assert(strcmp(sales_rank, "999,999,901") == 0);

  sscanf(" #24,675", pattern, &sales_rank);
  assert(strcmp(sales_rank, "24,675") == 0);

  sscanf("#1", pattern, &sales_rank);
  assert(strcmp(sales_rank, "1") == 0);


  return 0;
}
