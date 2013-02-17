#include <stdio.h>
#include <ctype.h>

int main(void)
{
  int i;
  int letter_counts[26] = {0};
  char ch;

  printf("Enter the first word: ");
  while ((ch = getchar()) != '\n') {
    if (isalpha(ch))
      letter_counts[tolower(ch) - 'a']++;
  }

  printf("Enter the second word: ");
  while ((ch = getchar()) != '\n') {
    if (isalpha(ch))
      letter_counts[tolower(ch) - 'a']--;
  }

  /*find a nonzero value*/
  for (i = 0; i < 26; i++) {
    if (letter_counts[i] > 0)
      break;
  }

  if (i == 26)
    printf("The words are anagrams\n");
  else
    printf("The words are not anagrams\n");

  return 0;
}
