#include <stdio.h>
#include <stdlib.h>
#include "../src/stackADT.h"

void exit_incorrect_nesting(Stack s)
{
  printf("Nesting is NOT correct\n");
  destroy(s);
  exit(EXIT_SUCCESS);
}
int main(void)
{
  int ch;
  Stack s = create();

  printf("Enter parentheses and/or braces: ");

  while ((ch = getchar()) != '\n')  {
    switch(ch) {
      case '(':
      case '{':
        push(s, ch);
        break;
      case ')':
        if (is_empty(s) || pop(s) != '(')
          exit_incorrect_nesting(s);
        break;
      case '}' :
        if (is_empty(s) || pop(s) != '{')
          exit_incorrect_nesting(s);
        break;
    }
  }

  if (is_empty(s))
    printf("Nesting is correct\n");
  else
    exit_incorrect_nesting(s);

  destroy(s);
  return 0;
}
