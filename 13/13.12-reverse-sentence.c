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
  char sentence[WORDS + 1][WORD_LEN] = {{'\0'}};

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
  char punctuation = '.';
  int input_ch;
  /* point to storage for first word string */
  char (*word_ptr)[WORD_LEN] = sentence;
  char *ch_ptr = word_ptr[0];

  while (word_ptr < sentence + WORDS && (input_ch = getchar()) != '\n') {
    if (input_ch == '!' || input_ch == '?') {
      /* defaults to '.' if nothing else is found */
      punctuation = input_ch;
    } else if (isalnum(input_ch) || input_ch == '-' ||input_ch == '\'' || input_ch == '_') {
      in_word = true;
      *ch_ptr = input_ch;
      ch_ptr++;
    } else if (in_word) {
      /*
         We've just found the ending word boundary;
         spaces and punc. will be ignored until we hit
         another word char and the 'in_word' flag gets set
      */
      in_word = false;

      /* terminate this word string */
      *ch_ptr = '\0';

      /* point to storage for next word string */
      word_ptr++;
      ch_ptr = word_ptr[0];
    }
  }

  /* did we end on a word character? */
  if (in_word)
    word_ptr++;

  *word_ptr[0] = punctuation;
  *word_ptr[1] = '\0';
}
