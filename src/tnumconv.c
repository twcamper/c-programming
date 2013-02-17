/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* tnumconv.c (Chapter 26, page 684) */
/* Tests C89 numeric conversion functions */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define CHK_VALID  printf("    %s           %s\n",         \
                          errno != ERANGE ? "Yes" : "No ", \
                          *ptr == '\0' ? "Yes" : "No")

int main(int argc, char *argv[])
{
  char *ptr;

  if (argc != 2) {
    printf("usage: tnumconv string\n");
    exit(EXIT_FAILURE);
  }

  printf("Function   Return Value\n");
  printf("--------   ------------\n");
  printf("atof       %g\n", atof(argv[1]));
  printf("atoi       %d\n", atoi(argv[1]));
  printf("atol       %ld\n\n", atol(argv[1]));

  printf("Function   Return Value   Valid?   "
         "String Consumed?\n"
         "--------   ------------   ------   "
         "----------------\n");

  errno = 0;
  printf("strtod     %-12g", strtod(argv[1], &ptr));
  CHK_VALID;

  errno = 0;
  printf("strtol     %-12ld", strtol(argv[1], &ptr, 10));
  CHK_VALID;

  errno = 0;
  printf("strtoul    %-12lu", strtoul(argv[1], &ptr, 10));
  CHK_VALID;

  return 0;
}
