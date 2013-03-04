#include <stdio.h>
#include <string.h>

#define SIZE 20

int main(void)
{

  char word[SIZE + 1];
  char smallest[SIZE + 1] = {127};
  char largest[SIZE + 1];

  while (strlen(word) != 4)  {
    printf("Enter a word: ");
    scanf("%20s", word);

    if (strcmp(word, smallest) < 0)
      strncpy(smallest, word, SIZE);
    else if (strcmp(word, largest) > 0)
      strncpy(largest, word, SIZE);
  }

  printf("Lowest word: %s\n", smallest);
  printf("Highest word: %s\n", largest);

  return 0;
}
