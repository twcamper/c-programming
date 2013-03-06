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
  while (*p == ' ') p++;  /* find first non-space character */
  first = *p;
  while (*p != ' ') p++;  /* find word boundary: first space after first p */
  while (*p == ' ') p++;  /* find start of last */
  for (;*p != '\n' && *p && *p != ' '; name++, p++)
    *name = *p;

  *name++ = ',';
  *name++ = ' ';
  *name++ = first;
  *name++ = '.';
  *name = '\0';
}
