#include <stdio.h>
#include <ctype.h>

int compute_scrabble_value(const char *word);

int main(void)
{
  char word[128];

  printf("Enter a word: ");

  scanf("%127s", word);

  printf("Scrabble Value: %d\n", compute_scrabble_value(word));
  return 0;
}
int compute_scrabble_value(const char *word)
{
  int scrabble_weights[26] = {
    1, //A
    3, //B
    3, //C
    2, //D
    1, //E
    4, //F
    2, //G
    4, //H
    1, //I
    8, //J
    5, //K
    1, //L
    3, //M
    1, //N
    1, //0
    3, //P
    10,//Q
    1, //R
    1, //S
    1, //T
    1, //U
    4, //V
    4, //W
    8, //X
    4, //Y
    10 //Z
  };

  char ch;
  int sum = 0;

  while (*word) {
    ch = toupper(*word++);
    if (ch >= 'A' && ch <= 'Z')
      sum += scrabble_weights[ch - 'A'];
  }

  return sum;
}
