#include <stdio.h>
#include <string.h>

#define SIZE 64
void reverse_name(char *name);

int main(void)
{
  char name[SIZE + 1];
  printf("Enter First Name and Last Name: ");
  fgets(name, sizeof(name), stdin);

  reverse_name(name);

  puts(name);
  return 0;
}
void reverse_name(char *name)
{
  /* char first[SIZE / 2], last[SIZE / 2]; */

  /* sscanf(name, " %s %s", first, last); */

  /* sprintf(name, "%s, %c.", last, first[0]); */

  char first, *p = name;
  int len;
  while (*p && *p == ' ') p++;  /* find first non-space character */
  first = *p;
  while (*p && *p != ' ') p++;  /* find word boundary: first space after first p */
  while (*p && *p == ' ') p++;  /* find start of last */
  for (len = 0; p[len] != '\n' && p[len] && p[len] != ' '; len++);
  sprintf(name, "%.*s, %c.", len, p, first);

}
