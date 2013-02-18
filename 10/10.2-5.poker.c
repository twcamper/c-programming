/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* poker.c (Chapter 10, page 233) */
/* Classifies a poker hand */

#include <stdbool.h>   /* C99 only */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

/* external variables */
bool straight, flush, four, three;
int pairs;   /* can be 0, 1, or 2 */

/* prototypes */
void read_cards(int [][2]);
void analyze_hand(int [][2]);
void print_result(void);
bool card_exists(int hand[][2], int rank, int suit);
bool is_flush(int hand[][2]);
bool is_straight(int hand[][2]);
void count_ranks_in_hand(int hand[][2], int ranks_in_hand[][2]);

/**********************************************************
 * main: Calls read_cards, analyze_hand, and print_result *
 *       repeatedly.                                      *
 **********************************************************/
int main(void)
{
  int hand[NUM_CARDS][2];

  for (;;) {
    read_cards(hand);
    analyze_hand(hand);
    print_result();
  }
}

/***************************************************************
 * read_cards: Reads the cards into the array hand[rank][suit],
 *             checks for bad cards and duplicate cards.  
 ***************************************************************/
void read_cards(int hand[][2])
{
  char ch;
  int rank, suit, card;
  bool bad_card;

  for (card = 0; card < NUM_CARDS; card++)
    hand[card][0] = hand[card][1] = 0;

  card = 0;
  while (card < NUM_CARDS) {
    bad_card = false;

    printf("Enter a card: ");

    switch (toupper(getchar())) {
      case '0': exit(EXIT_SUCCESS);
      case '2': rank = 2; break;
      case '3': rank = 3; break;
      case '4': rank = 4; break;
      case '5': rank = 5; break;
      case '6': rank = 6; break;
      case '7': rank = 7; break;
      case '8': rank = 8; break;
      case '9': rank = 9; break;
      case 'T': rank = 10; break;
      case 'J': rank = 11; break;
      case 'Q': rank = 12; break;
      case 'K': rank = 13; break;
      case 'A': rank = 14; break;
      default:            bad_card = true;
    }

    switch (toupper(getchar())) {
      case 'C': suit = 1; break;
      case 'D': suit = 2; break;
      case 'H': suit = 3; break;
      case 'S': suit = 4; break;
      default:            bad_card = true;
    }

    while ((ch = getchar()) != '\n')
      if (ch != ' ') bad_card = true;

    if (bad_card)
      printf("Bad card; ignored.\n");
    else if (card_exists(hand, rank, suit))
      printf("Duplicate card; ignored.\n");
    else {
      hand[card][0] = rank;
      hand[card][1] = suit;
      card++;
    }
  }  /* end hand */
}

/**********************************************************
 * analyze_hand: Determines whether the hand contains a   *
 *               straight, a flush, four-of-a-kind,       *
 *               and/or three-of-a-kind; determines the   *
 *               number of pairs; stores the results into *
 *               the external variables straight, flush,  *
 *               four, three, and pairs.                  *
 **********************************************************/
void analyze_hand(int hand[][2])
{
  int rank;
  int ranks_in_hand[NUM_CARDS][2];

  flush = is_flush(hand);
  if ((straight = is_straight(hand)))
    return;

  four = false;
  three = false;
  pairs = 0;

  count_ranks_in_hand(hand, ranks_in_hand);
  /* a hand can have from 1 to 5 ranks */

  /* [> check for 4-of-a-kind, 3-of-a-kind, and pairs <] */
  for (rank = 0; rank < NUM_CARDS && ranks_in_hand[rank][0] != 0; rank++) {
    if (ranks_in_hand[rank][1] == 4) four = true;
    if (ranks_in_hand[rank][1] == 3) three = true;
    if (ranks_in_hand[rank][1] == 2) pairs++;
  }
}

/**********************************************************
 * print_result: Prints the classification of the hand,   *
 *               based on the values of the external      *
 *               variables straight, flush, four, three,  *
 *               and pairs.                               *
 **********************************************************/
void print_result(void)
{
  if (straight && flush) printf("Straight flush");
  else if (four)         printf("Four of a kind");
  else if (three &&
           pairs == 1)   printf("Full house");
  else if (flush)        printf("Flush");
  else if (straight)     printf("Straight");
  else if (three)        printf("Three of a kind");
  else if (pairs == 2)   printf("Two pairs");
  else if (pairs == 1)   printf("Pair");
  else                   printf("High card");

  printf("\n\n");
}
bool card_exists(int hand[][2], int rank, int suit)
{
  for (int card = 0; card < NUM_CARDS; card++)
    if (hand[card][0] == rank && hand[card][1] == suit)
      return true;

  return false;
}
bool is_flush(int hand[][2])
{
  /* check for flush: all of same suit */
  if (hand[0][1] == hand[1][1] && hand[0][1] == hand[2][1] &&
      hand[0][1] == hand[3][1] && hand[0][1] == hand[4][1]) {
    return true;
  }
  return false;

}
bool is_straight(int hand[][2])
{
  /* check for straight: 5 consecutive ranks */
  int card, min_rank, max_rank;

  /* find the smallest and largest ranks */
  max_rank = min_rank = hand[0][0];
  for (card = 1; card < NUM_CARDS; card++) {
    if (hand[card][0] < min_rank)
      min_rank = hand[card][0];
    if (hand[card][0] > max_rank)
      max_rank = hand[card][0];
  }

  return max_rank - min_rank == NUM_CARDS - 1;
}
void count_ranks_in_hand(int hand[][2], int ranks_in_hand[][2])
{
  int card, rank;

  for (rank = 0; rank < NUM_CARDS; rank++)
    ranks_in_hand[rank][0] = ranks_in_hand[rank][1] = 0;

  /*
   * start with rank of first card in the hand
   * as our first hash key
   */
  ranks_in_hand[0][0] = hand[0][0];
  ranks_in_hand[0][1] = 1;

  for (card = 1; card < NUM_CARDS; card++)  {
    rank = 0;
    /* find the current hand's rank or the next empty element
     * which will be our next hash key
     */
    while (ranks_in_hand[rank][0] != hand[card][0] && ranks_in_hand[rank][0] != 0)
      rank++;
    /*
     * set the new hash key
     * because the current hand's rank
     * was not found in the hash
     */
    if (ranks_in_hand[rank][0] == 0)
      ranks_in_hand[rank][0] = hand[card][0];

    /* update the count value for the current hash key (a rank) */
    ranks_in_hand[rank][1]++;
  }
}