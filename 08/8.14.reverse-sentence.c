#include <stdio.h>

#define SPACE 0x20

int main(void)
{
  int boundary, i;
  char ch;
  char final_punctuation = 0;
  char sentence[255];

  printf("Enter a sentence: ");

  for (i = 0; (ch = getchar()) != '\n'; i++) {
    sentence[i] = ch;
  }
  /* terminate the string */
  sentence[i] = '\0';

  /*
   * back up, point to last character before the newline, which was not stored
   */
  i--;
  ch = sentence[i];
  if (ch == '.' || ch == '?' || ch == '!') {
    final_punctuation = ch;
    /* replace the punc. char to simplify the code below */
    sentence[i] = '\0';
  }

  while (i >= 0) {
    /* word boundary or start of string */
    if (sentence[i] == SPACE || i == 0) {
      boundary = i;

      /* if this is not the beginning of the string,
       * we need to point to the next char
       */
      if (sentence[i] == SPACE)
        i++;
      /* Print the word */
      while (sentence[i] != SPACE && sentence[i] != '\0') {
        printf("%c", sentence[i]);
        i++;
      }

      /* rewind to before the word we just printed */
      i = boundary;
      if (i == 0) {  // we've just printed the last (originally first) word
        if (final_punctuation)
          printf("%c", final_punctuation);
      } else {       // we've just printed any of the other words
        printf("%c", SPACE);
      }
    }
    i--;
  }
  printf("\n");

  return 0;
}
