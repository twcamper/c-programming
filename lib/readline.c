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
#define INT_WIDTH 10
#define SINT_WIDTH 11
int to_valid_int(int *n, char *str, int length)
{
  char *endptr;
  int length_converted;
  long conversion = 0;
  *n = 0;

  if (str[0] == '-') {
    if (length > SINT_WIDTH)
      return -1;
  }
  else if (length > INT_WIDTH)
    return -2;
  /*
     Convert input string to long first, because there is no 'strtoi'.
     strtol() provides the error checking we need to ensure we
     get the number the user entered.
  */
  errno = 0;
  conversion = strtol(str, &endptr, 10);

  if (errno != 0)
    return -3;

  /* did we stop reading early because of non-numerics? */
  length_converted = endptr - str;
  if (length_converted != length)
    return -4;

  /* the width is ok, but the value may not be */
  if (conversion < INT_MIN || conversion > INT_MAX) 
    return -5;

  *n = (int)conversion;
  return 0;
}
int read_int(int *n)
{
  int length_read;
  char digits[SINT_WIDTH + 2];
  /* store more than the max width of a signed int
     so we can detect if input would be truncated, which is one
     way a user's intended input can be changed
     */
  length_read  = read_line(digits, SINT_WIDTH + 2);
  return to_valid_int(n, digits, length_read);
}
int read_dollars_write_cents(int *n)
{
  int ch, i, decimal_places, has_decimal;

  /* Chars in a signed int,
   * + 2 extra decimal placess for 0 padding, 
   * + 1 for truncation test, + \0 */
  char digits[SINT_WIDTH + 4];

  while (isspace(ch = getchar()))
    ;

  i = decimal_places = has_decimal = 0;
  while (ch != '\n' && ch != EOF) {
    if (ch != '$' && ch != ',') {
      if (ch == '.')
        has_decimal++;
      else {
        if (has_decimal) decimal_places++;
        digits[i++] = ch;
      }
    }
    ch = getchar();
  }
  digits[i] = '\0';

  if (has_decimal > 1 || decimal_places > 2)
    return -1;

  if (decimal_places == 1)
    strcat(digits, "0");

  if (decimal_places == 0)
    strcat(digits, "00");

  return to_valid_int(n, digits, strlen(digits));
}
bool yes(char *prompt)
{
  static char response[2];
  printf("%s", prompt);
  read_line(response, 2);
  if (tolower(response[0]) == 'y')
    return true;

  return false;
}
