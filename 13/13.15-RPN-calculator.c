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
void empty_stack(void);
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
        case '+': push(pop() + pop());
          break;
        case '-': subtract();
          break;
        case '*': push(pop() * pop());
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
void tokenize(char *expression, char **tokens, int *token_count)
{
  register bool in_token = false;
  int t;
  char *ch_ptr;
  for (t = 0, ch_ptr = expression; *ch_ptr; ch_ptr++)  {
    if (isspace(*ch_ptr))  {
      if (in_token)
        /* this is the first char after a token,
         * and this is how we tokenize our string */
        *ch_ptr = '\0';
      in_token = false;
    } else  /* NOT A SPACE  */
      if (!in_token) {
        /* this is the frist char of our token, */
        /* so we put a pointer to it in our list */
        tokens[t++] = ch_ptr;
        in_token = true;
      }
  }
  *token_count = t;
}
