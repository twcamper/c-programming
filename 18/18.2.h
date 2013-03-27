/* 18.2.3 */
extern float a;

void f(register double b)
{

  static int c;
  auto char d;
}

/*
var     storage duration     scope      linkage
__________________________________________________
a       static                file       external
b       automatic             block      none
c       static                block      none
d       automatic             block      none

*/


/* 18.2.4 */

inf f(int i)
{
  static int j = 0;
  return i * j++;
}

/*
  first call, f(10) == 0
  sixth call, f(10) == 50
*/

/* 18.2.6 */

void print_error(const char *message)
{
  /* int n = 1;   needed to static */
  static int n = 1;
  printf("Error %d: %s\n", n++, message);
}
