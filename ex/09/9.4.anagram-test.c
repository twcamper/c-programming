#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define SIZE 26
void read_word(int letter_counts[]);
bool arrays_equal(int letter_counts[], int other[]);

int main(void)
{
  int letter_counts1[SIZE] = {0};
  int letter_counts2[SIZE] = {0};

  printf("Enter the first word: ");
  read_word(letter_counts1);

  printf("Enter the second word: ");
  read_word(letter_counts2);

  if (arrays_equal(letter_counts1, letter_counts2))
    printf("The words are anagrams\n");
  else
    printf("The words are not anagrams\n");

  return 0;
}

void read_word(int letter_counts[])
{
  char ch;
  while ((ch = getchar()) != '\n') {
    if (isalpha(ch))
      letter_counts[tolower(ch) - 'a']++;
  }
}
bool arrays_equal(int letter_counts[], int other[])
{
  int i;
  /*find a nonzero value*/
  for (i = 0; i < SIZE; i++) {
    if (letter_counts[i] != other[i])
      break;
  }
  return i == SIZE ? true : false;
}
