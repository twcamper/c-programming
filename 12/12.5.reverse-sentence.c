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
  int boundary;
  char ch, final_punctuation = 0;
  /*
   * back up, point to last character before the newline, which was not stored
   */
  int i = n - 1;
  ch = a[i];
  if (ch == '.' || ch == '?' || ch == '!') {
    final_punctuation = ch;
    /* replace the punc. char to simplify the code below */
    a[i] = '\0';
  }

  while (i >= 0) {
    /* word boundary or start of string */
    if (a[i] == SPACE || i == 0) {
      boundary = i;

      /* if this is not the beginning of the string,
       * we need to point to the next char
       */
      if (a[i] == SPACE)
        i++;
      /* Print the word */
      while (a[i] != SPACE && a[i] != '\0') {
        printf("%c", a[i]);
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
}
