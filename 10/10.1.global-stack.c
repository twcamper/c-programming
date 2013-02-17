#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_SIZE 100

char stack[STACK_SIZE];
int top = 0;

void empty(void);
bool is_empty(void);
bool is_full(void);
void push(char ch);
char pop(void);
void exit_stack_overflow(void);
void exit_stack_underflow(void);
void exit_incorrect_nesting(void);

int main(void)
{
  char ch;

  printf("Enter parentheses and/or braces: ");

  while ((ch = getchar()) != '\n')  {
    switch(ch) {
      case '(':
      case '{':
        push(ch);
        break;
      case ')':
        if (is_empty() || pop() != '(')
          exit_incorrect_nesting();
        break;
      case '}' :
        if (is_empty() || pop() != '{')
          exit_incorrect_nesting();
        break;
    }
  }

  if (is_empty())
    printf("Nesting is correct\n");
  else
    exit_incorrect_nesting();

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
void push(char ch)
{
  if (is_full())
    exit_stack_overflow();
  stack[top++] = ch;
}
char pop(void)
{
  if (is_empty())
    exit_stack_underflow();
  return stack[--top];
}
void exit_stack_overflow(void)
{
  fprintf(stderr, "Stack Overflow\n");
  exit(EXIT_FAILURE);
}
void exit_stack_underflow(void)
{
  fprintf(stderr, "Stack Underflow\n");
  exit(EXIT_FAILURE);
}
void exit_incorrect_nesting(void)
{
  printf("Nesting is NOT correct\n");
  exit(EXIT_SUCCESS);
}
