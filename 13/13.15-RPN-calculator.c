/* Reverse Polish Notation calculator */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE  100
#define TOKENS      200
#define BUFFER_SIZE 255
#define QUIT        -1

/* globals */
int stack[STACK_SIZE];
int top;
int input_error = 0;

/* prototypes */
void empty(void);
bool is_empty(void);
bool is_full(void);
void push(int operand);
int pop(void);
void subtract(void);
void divide(void);
void warn_stack_overflow(void);
void warn_stack_underflow(void);
void warn_incomplete_expression(void);
int evaluate(char *expression);
void tokenize(char *expression, char **tokens, int *token_count);

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
  if (is_full()) {
    warn_stack_overflow();
    input_error = 1;
    return;
  }
  stack[top++] = operand;
}
int pop(void)
{
  if (is_empty()) {
    warn_stack_underflow();
    input_error = 1;
    return 0;
  }
  return stack[--top];
}
void warn_stack_overflow(void)
{
  fprintf(stderr, "Expression is too complex.\n");
}
void warn_stack_underflow(void)
{
  fprintf(stderr, "Not enough operands in expression\n");
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
int evaluate(char *str)
{
  int token, token_count, value;
  char ch;
  char *expression[TOKENS];

  tokenize(str, expression, &token_count);

  for (token = 0; token < token_count; token++) {

    ch = expression[token][0];
    if (isdigit(ch))
      push((int) ch - '0');
    else if ( ch == '+')
      push(pop() + pop());
    else if ( ch == '-')
      subtract();
    else if ( ch == '*')
      push(pop() * pop());
    else if ( ch == '/')
      divide();
    else {
      /* Quit - neither an operator nor a digit operand */
      input_error = QUIT;
    }
    if (input_error)
      return input_error;
  }

  value = pop();
  if (!is_empty()) {
    warn_incomplete_expression();
    empty();
    return (input_error = 1);
  }
  return value;
}
void tokenize(char *expression, char **tokens, int *token_count)
{
  register bool in_token = false;
  int t;
  char *c;
  for (t = 0, c = expression; *c; c++)  {
    if (isspace(*c))  {
      if (in_token)
        /* this is the first char after a token,
         * and this is how we tokenize our string */
        *c = '\0';
      in_token = false;
    } else  /* NOT A SPACE  */
      if (!in_token) {
        /* this is the frist char of our token, */
        /* so we put a pointer to it in our list */
        tokens[t++] = c;
        in_token = true;
      }
  }
  *token_count = t;
}
