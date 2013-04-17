/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* canopen.c (Chapter 22, page 547) */
/* Checks whether a file can be opened for reading */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool readable(char *file)
{
  FILE *fp;
  if ((fp = fopen(file, "rb")) == NULL)
    return false;

  fclose(fp);

  return true;
}

int main(int argc, char *argv[])
{

  if (argc < 2) {
    printf("usage: %s  <filenames>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++)
    if (readable(argv[i]))
      printf("Y: %s\n", argv[i]);
    else
      printf("N: %s\n", argv[i]);

  return 0;
}
