/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* readline.c (Chapter 16, page 395) */

#include "readline.h"

int read_line(char str[], int n)
{
  int ch, i = 0;

  while (isspace(ch = getchar()))
    ;
  while (ch != '\n' && ch != EOF) {
    if (i < n)
      str[i++] = ch;
    ch = getchar();
  }
  str[i] = '\0';
  return i;
}
int read_int(int *n)
{
  char *endptr, digits[SINT_WIDTH + 2];
  int length_read, length_converted;
  long conversion = 0;
  *n = 0;

  /* store more than the max width of a signed int
     so we can detect if input would be truncated, which is one
     way a user's intended input can be changed
     */
  length_read  = read_line(digits, SINT_WIDTH + 2);

  if (digits[0] == '-') {
    if (length_read > SINT_WIDTH)
      return -1;
  }
  else if (length_read > INT_WIDTH)
    return -2;
  /*
     Convert input string to long first, because there is no 'strtoi'.
     strtol() provides the error checking we need to ensure we
     get the number the user entered.
  */
  errno = 0;
  conversion = strtol(digits, &endptr, 10);

  /* did we stop reading early because of non-numerics? */
  length_converted = endptr - digits;
  if (errno != 0 || length_converted != length_read)
    return -3;

  /* the width is ok, but the value may not be */
  if (conversion < INT_MIN || conversion > INT_MAX) 
    return -4;

  *n = (int)conversion;
  return 0;
}
