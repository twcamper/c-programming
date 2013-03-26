#include <stdio.h>
#include <stdlib.h>
#include "readline.h"
#include "error.h"

#define MAX_WORDS 1024
#define WORD_LEN  28

int main(void)
{
  char input[WORD_LEN + 1];
  char *words[MAX_WORDS];
  int i, word_count = 0;

  for(;;) {
    if (word_count == MAX_WORDS) {
      printf("Word max %d reached.", word_count);
      break;
    }

    printf("Word? ");
    read_line(input, WORD_LEN);
    if (input[0] == '0')
      break;

    /* find alphabetic position to insert word into */
    for (i = 0; i < word_count; i++)
      if (strcmp(input, words[i]) < 0)
        break;

    /* shift everybody else down to open up a hole at i*/
    for (int j = word_count; j > i; j--)
      words[j] = words[j - 1];

    /* on my 64 bit machine, malloc will probably allocate nearly an MB anyway! */
    words[i] = malloc(strlen(input) + 1);
    if (!words[i])
      memory_error(__FILE__, __LINE__, __func__);

    strcpy(words[i], input);
    word_count++;
  }

  for (i = 0; i < word_count; i++) {
    printf("%s\n", words[i]);
    free(words[i]);
  }

  return 0;
}
