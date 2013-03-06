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
  /*
   * Average word length == total number of word characters / number of words.
   *
   * Look at each char in the string
   *   if it is a tic
   *     if in_word
   *       increment other_single_quotes  (could be an apostrophe or a
   *       correctly placed close quote)
   *     else
   *       if open_quotes is odd  (we're looking for a close quote, so
   *       this one is placed after a bad space or good punctuation)
   *         increment other_single_quotes
   *       else
   *         increment open_quotes
   *   else if it is a word char
   *      set 'in_word' flag
   *      increment char count
   *   else
   *      if in_word is set
   *        unset it
   *        increment word count
   *
   * adjust for apostrophes  (other_single_quotes must >= open_quotes)
   *   if other_single_quotes >= open_quotes
   *     apostrophes = other_single_quotes - open_quotes
   *   else
   *     apostrophes = 0 because the input has incorrect punctuation, i.e. unbalanced quotes
   *   chars += apostrophes
   * return chars / words
   */
  double chars, words;
  chars = words = 0.0;
  register bool in_word = false;

  for (const char *c = sentence; *c && *c != '\n'; c++)  {
    if (isalnum(*c) || *c == '-' || *c == '_') {
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

  return chars / words;
}
