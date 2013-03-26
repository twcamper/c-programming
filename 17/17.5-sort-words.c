#include <stdio.h>
#include <stdlib.h>
#include "readline.h"
#include "error.h"
#include <assert.h>

#define MAX_WORDS 1024
#define WORD_LEN  28
int compare_words(const void *a, const void *b)
{
  char **string_a = (char **)a;
  char **string_b = (char **)b;

  return strcmp(*string_a, *string_b);
}
int main(void)
{
  char input[WORD_LEN + 1];
  char *words[MAX_WORDS];
  int word_count = 0;

  for(;;) {
    if (word_count == MAX_WORDS) {
      printf("Word max %d reached.", word_count);
      break;
    }

    printf("Word? ");
    read_line(input, WORD_LEN);
    if (input[0] == '0')
      break;

    /* on my 64 bit machine, malloc will probably allocate nearly an MB anyway! */
    words[word_count] = malloc(strlen(input) + 1);
    if (!words[word_count])
      memory_error(__FILE__, __LINE__, __func__);

    strcpy(words[word_count], input);
    word_count++;
  }

  qsort(words, word_count, sizeof(char *), compare_words);

  for (int i = 0; i < word_count; i++) {
    printf("%s\n", words[i]);
    free(words[i]);
  }

  return 0;
}
