#include <stdio.h>
#include <string.h>
#include "tokenize.h"
#include "stack.h"

#define BUFFER_SIZE 255
#define QUIT        -1
#define TOKENS      200

int input_error = 0;

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
void add()
{
  push(pop() + pop());
}
void multiply()
{
  push(pop() * pop());
}

int evaluate(char *expression)
{
  int i, token_count, value;
  char *t_ptr;
  char *token_pointers[TOKENS];   /* list of addresses within the expression string */

  empty_stack();

  /* pepper our expression input string with terminators (NULL chars) */
  tokenize(expression, token_pointers, &token_count);

  for (i = 0; i < token_count; i++) {
    /* the next substring in our NULL delimited input string */
    t_ptr = token_pointers[i];

    /*
       Is the token a number?
       It may begin with (or be) a digit,
       OR if it's longer than 1 char,
         it must be '-' then at least one digit
    */
    if (isdigit(t_ptr[0]) || (strlen(t_ptr) > 1 && isdigit(t_ptr[1]) && t_ptr[0] == '-'))
      push(atoi(t_ptr));
    else
      switch(t_ptr[0])  {
        case '+': add();
          break;
        case '-': subtract();
          break;
        case '*': multiply();
          break;
        case '/': divide();
          break;
        default:
          /* Quit - neither an operator nor a digit operand */
          input_error = QUIT;
      }
    if (input_error)
      return input_error;
  }

  value = pop();
  if (!is_empty()) {
    warn_incomplete_expression();
    return (input_error = 1);
  }
  return value;
}

int main(void)
{
  char expression[BUFFER_SIZE + 1];
  int value;

  for (;;) {
    printf("Enter an RPN expression: ");
    fgets(expression, (int) sizeof(expression), stdin);
    input_error = 0;
    value = evaluate(expression);
    if (!input_error)
      printf("Value: %d\n",  value);
    else if (input_error == QUIT)
      break;
  }

  return 0;
}
