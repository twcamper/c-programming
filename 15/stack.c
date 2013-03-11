#include "stack.h"

#define STACK_SIZE  100

int stack[STACK_SIZE];
int top = 0;

void empty_stack(void)
{
  top = 0;
}
bool is_empty(void)
{
  return top == 0;
}
bool is_full(void)
{
  return top == STACK_SIZE;
}
void push(int operand)
{
  if (is_full()) {
    exit_stack_overflow();
    return;
  }
  stack[top++] = operand;
}
int pop(void)
{
  if (is_empty()) {
    exit_stack_underflow();
    return 0;
  }
  return stack[--top];
}
void exit_stack_overflow(void)
{
  fprintf(stderr, "Stack Overflow.\n");
  exit(EXIT_FAILURE);
}
void exit_stack_underflow(void)
{
  fprintf(stderr, "Stack Underflow\n");
  exit(EXIT_FAILURE);
}
