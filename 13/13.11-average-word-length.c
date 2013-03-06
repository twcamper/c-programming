#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

double compute_average_word_length(const char *sentence);

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s \"Enter a sentence in quotes.\"\n", argv[0]);
    return 1;
  }

  printf("%.2f\n", compute_average_word_length(argv[1]));
  return 0;
}

double compute_average_word_length(const char *sentence)
{
  register bool in_word = false;
  double chars, words, apostrophes;
  int open_quotes, other_single_quotes;

  open_quotes = other_single_quotes = 0;
  chars = words = apostrophes = 0.0;

  for (const char *c = sentence; *c && *c != '\n'; c++)  {
    if (*c == '\'') {
      if (in_word)
        /* could be an apostrophe or a close-quote right after a word */
        other_single_quotes++;
      else {
        if (open_quotes % 2 > 0)
          /*
             Count of open-quotes is odd, so we're looking for a close quote.
             This one is placed after punctuation or an extra space after a word.
          */
          other_single_quotes++;
        else
          open_quotes++;
      }
    } else if (isalnum(*c) || *c == '-' || *c == '_') {
      in_word = true;
      chars++;
    } else if (in_word) {
      /* we just left the word: we won't be here in the case of initial or multiple spaces */
      in_word = false;
      words++;
    }
  }

  /* did we terminate on a word character? */
  if (in_word)
    words++;

  /* adjust char count for apostrophes, but only if the single quotes balance out */
  if (other_single_quotes >= open_quotes)
    apostrophes = (double) (other_single_quotes - open_quotes);
  chars += apostrophes;

  return chars / words;
}
