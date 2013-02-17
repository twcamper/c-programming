/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* tsignal.c (Chapter 24, page 634) */
/* Tests signals */

#include <signal.h>
#include <stdio.h>

void handler(int sig);
void raise_sig(void);

int main(void)
{
  void (*orig_handler)(int);

  printf("Installing handler for signal %d\n", SIGINT);
  orig_handler = signal(SIGINT, handler);
  raise_sig();

  printf("Changing handler to SIG_IGN\n");
  signal(SIGINT, SIG_IGN);
  raise_sig();

  printf("Restoring original handler\n");
  signal(SIGINT, orig_handler);
  raise_sig();

  printf("Program terminates normally\n");
  return 0;
}

void handler(int sig)
{
  printf("Handler called for signal %d\n", sig);
}

void raise_sig(void)
{
  raise(SIGINT);
}
