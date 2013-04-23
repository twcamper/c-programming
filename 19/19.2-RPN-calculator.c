#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenize.h"
#include "../src/stackADT.h"

#define BUFFER_SIZE 255
#define QUIT        -1
#define TOKENS      200

static int input_error = 0;

void warn_incomplete_expression(void)
{
  fprintf(stderr, "Incomplete expression\n");
}
void subtract(Stack s)
{
  int subtrahend = pop(s);
  int minuend = pop(s);

  push(s, minuend - subtrahend);
}
void divide(Stack s)
{
  int divisor = pop(s);
  int dividend = pop(s);

  push(s, dividend / divisor);
}
void add(Stack s)
{
  push(s, pop(s) + pop(s));
}
void multiply(Stack s)
{
  push(s, pop(s) * pop(s));
}

int evaluate(Stack s, char *expression)
{
  int i, token_count, value;
  char *t_ptr;
  char *token_pointers[TOKENS];   /* list of addresses within the expression string */

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
      push(s, atoi(t_ptr));
    else
      switch(t_ptr[0])  {
        case '+': add(s);
          break;
        case '-': subtract(s);
          break;
        case '*': multiply(s);
          break;
        case '/': divide(s);
          break;
        default:
          /* Quit - neither an operator nor a digit operand */
          input_error = QUIT;
      }
    if (input_error)
      return input_error;
  }

  value = pop(s);
  if (!is_empty(s)) {
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
    Stack s = create();
    value = evaluate(s, expression);
    destroy(s);
    if (!input_error)
      printf("Value: %d\n",  value);
    else if (input_error == QUIT)
      break;
  }

  return 0;
}
