#include <stdio.h>

#define SPACE 0x20

void print_reversed(char *a, int n);

int main(void)
{
  int i;
  char ch;
  char sentence[255];

  printf("Enter a sentence: ");

  for (i = 0; (ch = getchar()) != '\n'; i++) {
    sentence[i] = ch;
  }
  /* terminate the string */
  sentence[i] = '\0';

  print_reversed(sentence, i);
  return 0;
}
void print_reversed(char *a, int n)
{
  char *boundary, *ch_ptr, final_punctuation = 0;
  /*
   * back up, point to last character before the newline, which was not stored
   */
  ch_ptr = a + (n - 1);
  if (*ch_ptr == '.' || *ch_ptr == '?' || *ch_ptr == '!') {
    final_punctuation = *ch_ptr;
    /* replace the punc. char to simplify the code below */
    *ch_ptr = '\0';
  }

  while (ch_ptr >= a) {
    /* word boundary or start of string */
    if (*ch_ptr == SPACE || ch_ptr == a) {
      boundary = ch_ptr;

      /* if this is not the beginning of the string,
       * we need to point to the next char
       */
      if (*ch_ptr == SPACE)
        ch_ptr++;
      /* Print the word */
      while (*ch_ptr != SPACE && *ch_ptr != '\0') {
        printf("%c", *ch_ptr);
        ch_ptr++;
      }

      /* rewind to before the word we just printed */
      ch_ptr = boundary;
      if (ch_ptr == a) {  // we've just printed the last (originally first) word
        if (final_punctuation)
          printf("%c", final_punctuation);
      } else {       // we've just printed any of the other words
        printf("%c", SPACE);
      }
    }
    ch_ptr--;
  }
  printf("\n");
}
