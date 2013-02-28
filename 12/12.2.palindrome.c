#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define SIZE 120
bool is_palindrome(char *a, int n);

int main(void)
{
  char ch, message[SIZE];

  int i = 0;
  printf("Enter a phrase, perhaps palindromic: ");

  while (i < SIZE && (ch = getchar()) != '\n')
    if (isalpha(ch))
      message[i++] = toupper(ch);

  if (is_palindrome(message, i - 1))
    printf("Palindrome Detected, Captain!\n");
  else
    printf("No Palindrome found, Sir!\n");

  return 0;
}

bool is_palindrome(char *a, int n)
{
  char *left, *right;
  for (left = a, right = a + n; left <= right; left++, right--)
    if (*left != *right)
      return false;

  return true;
}
