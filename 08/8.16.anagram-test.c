#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define SIZE 28

bool are_anagrams(const char *word1, const char *word2)
{
  int letter_counts[26] = {0};

  while (*word1) {
    if (isalpha(*word1))
      letter_counts[tolower(*word1) - 'a']++;
    word1++;
  }

  while (*word2)  {
    if (isalpha(*word2))
      letter_counts[tolower(*word2) - 'a']--;
    word2++;
  }

  /* find a nonzero value */
  for (int i = 0; i < 26; i++) {
    if (letter_counts[i] != 0)
      return false;
  }
  return true;
}

void read_word(char *w, int n)
{
  char ch, *p;
  for (p = w;(ch = getchar()) != '\n'; p++)
    if (p < (w + n))
      *p = ch;

  *p = '\0';
}

int main(void)
{
  char w1[SIZE], w2[SIZE];

  printf("Enter the first word: ");
  read_word(w1, SIZE);

  printf("Enter the second word: ");
  read_word(w2, SIZE);

  if (are_anagrams(w1, w2))
    printf("The words are anagrams\n");
  else
    printf("The words are not anagrams\n");

  return 0;
}
