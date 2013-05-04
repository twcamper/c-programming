/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* xor.c (Chapter 20, page 515) */
/* Performs XOR encryption */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define KEY '&'

static void exit_error(char *program, char *file)
{
  fprintf(stderr, "%s: %s: %s\n", program, file, strerror(errno));
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  int ch;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *in, *out;

  if ((in = fopen(argv[1], "rb")) == NULL)
    exit_error(argv[0], argv[1]);

  if ((out = fopen(argv[2], "wb")) == NULL)
    exit_error(argv[0], argv[2]);

  while ((ch = fgetc(in)) != EOF) {
    if (fputc(ch ^ KEY, out) == EOF)
      exit_error(argv[0], argv[2]);
  }

  return 0;
}
