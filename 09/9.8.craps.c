#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

int roll_dice(void);
bool play_game(void);
bool win(void);
bool lose(void);
void print_roll(int);

int main(void)
{
  char response[2];
  int wins, losses;
  wins = losses = 0;

  do {
    if (play_game())
      wins++;
    else
      losses++;

    printf("Play again? ");
    scanf("%1s", response);
  } while ( response[0] == 'y' || response[0] == 'Y');

  printf("Wins: %d\tLosses: %d\n", wins, losses);

  return 0;
}

/*
 * sum of 2 dice will be from 2 to 12 = (0..10 + 2)
 */ 
int roll_dice(void)
{
  return (rand() % 11) + 2;
}
bool play_game(void)
{
  srand((unsigned) time(NULL));
  int sum, point;

  printf("\n");

  /*
   * First Roll
   */
  sum = roll_dice();
  print_roll(sum);
  if (sum == 7 || sum == 11)
    return win();
  if (sum < 4 || sum == 12)
    return lose();

  point = sum;
  for (;;) {
    sum = roll_dice();
    print_roll(sum);
    if (sum == 7)
      return lose();
    if (sum == point)
      return win();
  }

}

bool win(void)
{
  printf("You win!\n\n");
  return true;
}
bool lose(void)
{
  printf("You lose!\n\n");
  return false;
}
void print_roll(int sum)
{
  printf("dice = %d\n", sum);
}
