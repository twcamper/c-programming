/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* tsetjmp.c (Chapter 24, page 636) */
/* Tests setjmp/longjmp */

#include <setjmp.h>
#include <stdio.h>

jmp_buf env;

void f1(void);
void f2(void);

int main(void)
{
  if (setjmp(env) == 0)
    printf("setjmp returned 0\n");
  else {
    printf("Program terminates: longjmp called\n");
    return 0;
  }

  f1();
  printf("Program terminates normally\n");
  return 0;
}

void f1(void)
{
  printf("f1 begins\n");
  f2();
  printf("f1 returns\n");
}

void f2(void)
{
  printf("f2 begins\n");
  longjmp(env, 1);
  printf("f2 returns\n");
}
