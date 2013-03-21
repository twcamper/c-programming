#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *duplicate1(char *s)
{
  char *p;
  if ((p = malloc(strlen(s) + 1)) == NULL)
    return NULL;
  strcpy(p,s);
  return p;
}
char *duplicate2(char *s)
{
  char *target, *p;
  if ((p = malloc(strlen(s) + 1)) == NULL)
    return NULL;
  target = p;
  while (( *p++ = *s++ ));
  return target;
}
char *duplicate_stupidly(char *s)
{
  if (!*s)
    return "";

  /* initialize for the first call to realloc, */
  /* which acts like malloc if given NULL */
  char *p = NULL;

  /* Don't get the size up front, "just" reallocate
   * our block every byte until we're not null */
  int i = 0;
  do {
    if ((p = realloc(p, i + 1)) == NULL)
      return NULL;
  } while ((p[i++] = *s++));

  return p;
}
int main(void)
{
  char *t, *s = "Bifurcate!\n And Do It Well, you bastards!\n";

  /* t = duplicate1(s); */
  /* t = duplicate2(s); */
  t = duplicate_stupidly(s);
  printf("%p: %s\n", &t, t);
  free(t);

  return 0;
}
