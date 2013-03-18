/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* readline.h (Chapter 16, page 395) */

#ifndef READLINE_H
#define READLINE_H
#include <stdio.h>
/**********************************************************
 * read_line: Skips leading white-space characters, then  *
 *            reads the remainder of the input line and   *
 *            stores it in str. Truncates the line if its *
 *            length exceeds n. Returns the number of     *
 *            characters stored.                          *
 **********************************************************/
int read_line(char str[], int n);


/**********************************************************
 * read_int: Initializes n to 0, but only stores a value 
 *           in n if the string entered is a valid int 
 *           between INT_MIN and INT_MAX.
 *
 *           Returns 0 on success, non-zero for input
 *           containing non-digits (neg '-' is ok) or value
 *           out of INT range.
 **********************************************************/
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#define INT_WIDTH 10
#define SINT_WIDTH 11
int read_int(int *n);
#endif