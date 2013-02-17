#include <stdio.h>
#include <stdlib.h>

int play_game(void)
{
  return rand() % 2;
}

int main(void)
{
  char response;
  int wins, losses;
  wins = losses = 0;

  do {
    if (play_game()) {
      printf("Win!\n");
      wins++;
    } else {
      printf("Lose.\n");
      losses++;
    }

    printf("Play again? ");
    /* 
     * this format string (" %c") works, and causes no problems
     */
    /*scanf(" %c", &response);*/

    /*
     * with this format string, (" %s") 
     * the value of 'losses' gets reset to 0
     */
    scanf(" %s", &response);
  } while ( response == 'y' || response == 'Y');

  printf("Wins: %d\tLosses: %d\n", wins, losses);

  return 0;
}
