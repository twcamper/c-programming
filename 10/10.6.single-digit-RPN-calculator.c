/* Reverse Polish Notation calculator */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_SIZE 100

/* globals */
int stack[STACK_SIZE];
int top;

/* prototypes */
void empty(void);
bool is_empty(void);
bool is_full(void);
void push(int operand);
char pop(void);
void exit_stack_overflow(void);
void exit_stack_underflow(void);

int main(void)
{
  char ch;

  for (;;) {
    printf("Enter an RPN expression: ");
    for (;;) {
      scanf(" %1c", &ch);

      if (ch >= '0' && ch <= '9')
        push((int) ch - '0');
      else if ( ch == '+')
        push(pop() + pop());
      else if ( ch == '-')
        push(pop() - pop());
      else if ( ch == '*')
        push(pop() * pop());
      else if ( ch == '/')
        push(pop() / pop());
      else
        break;
    }

    if (ch == '=') {
      printf("Value: %d\n", pop());
      empty();
    } else
      break;
  }


  return 0;
}
void empty(void)
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
  if (is_full())
    exit_stack_overflow();
  stack[top++] = operand;
}
char pop(void)
{
  if (is_empty())
    exit_stack_underflow();
  return stack[--top];
}
void exit_stack_overflow(void)
{
  fprintf(stderr, "Expression is too complex.\n");
  exit(EXIT_FAILURE);
}
void exit_stack_underflow(void)
{
  fprintf(stderr, "Not enough operands\n");
  exit(EXIT_FAILURE);
}
