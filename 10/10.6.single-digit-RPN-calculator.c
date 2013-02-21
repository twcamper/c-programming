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
void subtract(void);
void divide(void);
void exit_stack_overflow(void);
void exit_stack_underflow(void);
void warn_incomplete_expression(void);

int main(void)
{
  char ch;
  int value;

  for (;;) {
    printf("Enter an RPN expression: ");
    for (;;) {
      scanf(" %1c", &ch);

      if (ch >= '0' && ch <= '9')
        push((int) ch - '0');
      else if ( ch == '+')
        push(pop() + pop());
      else if ( ch == '-')
        subtract();
      else if ( ch == '*')
        push(pop() * pop());
      else if ( ch == '/')
        divide();
      else
        break;
    }

    if (ch == '=') {
      value = pop();
      if (is_empty()) {
        printf("Value: %d\n",  value);
      } else {
        warn_incomplete_expression();
        empty();
      }
    } else {
      /* Quit - neither an operator nor a digit operand */
      break;
    }
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
  fprintf(stderr, "Not enough operands in expression\n");
  exit(EXIT_FAILURE);
}
void warn_incomplete_expression(void)
{
  fprintf(stderr, "Incomplete expression\n");
}
void subtract(void)
{
  int subtrahend = pop();
  int minuend = pop();

  push(minuend - subtrahend);
}
void divide(void)
{
  int divisor = pop();
  int dividend = pop();

  push(dividend / divisor);
}
