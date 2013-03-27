/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* remind2.c (Chapter 17, page 418) */
/* Prints a one-month reminder list (dynamic string version) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_REMIND 50   /* maximum number of reminders */
#define MSG_LEN 120     /* max length of reminder message */

struct vstring {
  int size;
  char s[];
};

int read_line(char str[], int n);

int main(void)
{
  struct vstring  *reminders[MAX_REMIND];
  char day_str[3], msg_str[MSG_LEN];
  int len, day, i, j, num_remind = 0;

  for (;;) {
    if (num_remind == MAX_REMIND) {
      printf("-- No space left --\n");
      break;
    }

    printf("Enter day and reminder: ");
    scanf("%2d", &day);
    if (day == 0)
      break;
    sprintf(day_str, "%2d", day);

    len = 3;  /* dd + space */
    len += read_line(msg_str, MSG_LEN);

    for (i = 0; i < num_remind; i++)
      if (strcmp(day_str, reminders[i]->s) < 0)
        break;
    for (j = num_remind; j > i; j--)
      reminders[j] = reminders[j-1];

    reminders[i] = malloc(2 + sizeof(struct vstring) + len);
    if (reminders[i] == NULL) {
      printf("-- No space left --\n");
      break;
    }
    reminders[i]->size = len;

    strcpy(reminders[i]->s, day_str);
    strcat(reminders[i]->s, " ");
    strcat(reminders[i]->s, msg_str);

    num_remind++;
  }

  printf("\nDay Reminder\n");
  for (i = 0; i < num_remind; i++)  {
    printf(" %.*s\n", reminders[i]->size, reminders[i]->s);
  }

  return 0;
}

int read_line(char str[], int n)
{
  int ch, i = 0;

  while (isspace(ch = getchar()));

  while (ch != '\n' && ch != EOF) {
    if (i < n)
      str[i++] = ch;
    ch = getchar();
  }
  return i;
}
