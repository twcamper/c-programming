#include <stdio.h>
#include <ctype.h>
#define SIZE 20

int read_line(char s[], int n);
void print_header(char *header);

int main(void)
{
  char str1[SIZE + 1];
  char str2[SIZE + 1];
  printf("Enter a string:\n");
  print_header("+---------");

  printf("String 1 (%d):\n%s\n", read_line(str1, SIZE), str1);
  printf("String 2 (%d):\n%s\n", read_line(str2, SIZE), str2);

  print_header("0123456789");

  return 0;
}

/* Reads a line up to n characters */
int read_line(char s[], int n)
{
  int ch, i = 0;

  /* ignore leading whitespace */
  while (isspace(ch = getchar()));

  /* the first non-whitespace character */
  s[i++] = ch;

  while ((ch = getchar()) != '\n' && i < n)
    s[i++] = ch;

  s[i] = '\0';

  return i;
}
void print_header(char *header)
{
  for (int i = 0; i < SIZE / 10; i++) printf(header);
  puts("");
}
