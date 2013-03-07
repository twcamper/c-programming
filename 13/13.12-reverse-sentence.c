#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define WORDS 30
#define WORD_LEN (20 + 1)

void print_reversed(char sentence[][WORD_LEN]);
void read(char sentence[][WORD_LEN]);

int main(void)
{
  /* extra 'word' array to hold final punctation */
  char sentence[WORDS + 1][WORD_LEN] = {{0}};

  read(sentence);

  print_reversed(sentence);

  return 0;
}
void print_reversed(char sentence[][WORD_LEN])
{
  int word = 0;
  /* find last word: this is where the final punctuation will be */
  while (sentence[word][0]) word++;

  char punctuation = sentence[--word][0];

  for (word-- ;word >= 0; word--)
    printf(" %s", sentence[word]);

  printf("%c\n", punctuation);
}
void read(char sentence[][WORD_LEN])
{
  register bool in_word = false;
  char ch, punctuation = '.';
  int i, word;
  i = word = 0;

  while ((ch = getchar()) != '\n') {
    if (ch == '!' || ch == '?') {
      /* defaults to '.' if nothing else is found */
      punctuation = ch;
    } else if (isalnum(ch) || ch == '-' ||ch == '\'' || ch == '_') {
      in_word = true;
      sentence[word][i++] = ch;
    } else if (in_word) {
      /*
         we've just found the ending word boundary;
         space and punc. will be ignored until we hit
         another word char and the 'in_word' flag gets set
      */
      in_word = false;
      sentence[word++][i] = '\0';
      i = 0;
    }
  }

  /* did we end on a word character? */
  if (in_word)
    word++;

  sentence[word][0] = punctuation;
  sentence[word][1] = '\0';
}
