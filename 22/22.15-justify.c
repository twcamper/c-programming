/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* justify.c (Chapter 15, page 363) */
/* Formats a file of text */

#include <string.h>
#include "line.h"
#include "word.h"
#include "error.h"

#define MAX_WORD_LEN 28

int main(int argc, char *argv[])
{
  char word[MAX_WORD_LEN+2];
  int word_len;

  if (argc != 3)
    invocation_error(argv[0], "[input file] [output file]");

  if (!freopen(argv[1], "r", stdin))
    exit_error(argv[0], argv[1]);

  if (!freopen(argv[2], "w", stdout)) {
    if (fclose(stdin) == EOF)
      perror(argv[1]);
    exit_error(argv[0], argv[2]);
  }

  clear_line();
  for (;;) {
    word_len = read_word(word, MAX_WORD_LEN+1);
    if (word_len == 0) {
      flush_line();
      return 0;
    }
    if (word_len + 1 > space_remaining()) {
      write_line();
      clear_line();
    }
    add_word(word);
  }
  if (fclose(stdin) == EOF)
    perror(argv[1]);
  if (fclose(stdout) == EOF)
    perror(argv[2]);
}
