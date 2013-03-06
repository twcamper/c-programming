#include <stdio.h>
#include <ctype.h>

#define SIZE 1024

int count_vowels(const char *sentence);

int main(void)
{
  char s[SIZE + 1];

  printf("Enter a sentence: ");
  fgets(s, sizeof(s), stdin);

  printf("Vowel count: %d\n", count_vowels(s));
  return 0;
}
int count_vowels(const char *sentence)
{
  int sum = 0;
  while (*sentence) {
    switch(tolower(*sentence++)) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        sum++;
        break;
    }
  }

  return sum;
}
