#include <stdbool.h>

#define STACK_SIZE 100
int contents[STACK_SIZE];
int *top_ptr = contents;

void empty(void);
bool is_empty(void);
bool is_full(void);

int main(void)
{
  return 0;
}

void empty(void)
{
  top_ptr = contents;
  /* top_ptr = &contents[0]; */
}
bool is_empty(void)
{
  return top_ptr == contents;
  /* return top_ptr == &contents[0]; */
}
bool is_full(void)
{
  return top_ptr == &contents[STACK_SIZE];
}
