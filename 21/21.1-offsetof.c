#include <stdio.h>
#include <stddef.h>

struct s {
  char a;
  int b[2];
  float c;
};

int main(void)
{
  printf("        offset   size\n");
  printf("struct s:  %ld\t%ld\n", offsetof(struct s,a), sizeof(struct s));
  /* Seems to be a 3-byte hole after the char member 'a' */
  printf("s.a     :  %ld\t%ld\n", offsetof(struct s,a), sizeof(((struct s*)0)->a));
  printf("s.b     :  %ld\t%ld\n", offsetof(struct s,b), sizeof(((struct s*)0)->b));
  printf("s.b[1]  :  %ld\t%ld\n", offsetof(struct s,b[1]), sizeof(((struct s*)0)->b[1]));
  printf("s.c     :  %ld\t%ld\n", offsetof(struct s,c), sizeof(((struct s*)0)->c));

  return 0;
}
