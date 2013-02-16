#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void read_word(int letter_counts[], int factor);
bool is_all_zeroes(int letter_counts[]);

int main(void)
{
  int letter_counts[26] = {0};

  printf("Enter the first word: ");
  read_word(letter_counts, 1);

  printf("Enter the second word: ");
  read_word(letter_counts, -1);

  if (is_all_zeroes(letter_counts))
    printf("The words are anagrams\n");
  else
    printf("The words are not anagrams\n");

  return 0;
}

void read_word(int letter_counts[], int factor)
{
  char ch;
  while ((ch = getchar()) != '\n') {
    if (isalpha(ch))
      letter_counts[tolower(ch) - 'a'] += factor;
  }
}
bool is_all_zeroes(int letter_counts[])
{
  int i;
  /*find a nonzero value*/
  for (i = 0; i < 26; i++) {
    if (letter_counts[i] != 0)
      break;
  }
  return i == 26 ? true : false;
}
