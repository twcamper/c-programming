/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* line.c (Chapter 15, page 364) */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "line.h"

#define MAX_LINE_LEN 80

typedef struct node {
  char word[MAX_LINE_LEN];
  struct node *next;
} Node;

Node *line;
Node *tail;
int line_len = 0;
int num_words = 0;

Node *create(void)
{
  Node *new_node = malloc(sizeof(Node));
  if (!new_node) {
    fprintf(stderr, "Memory Allocation Error: malloc() at %s: %d (%s)\n", __FILE__, __LINE__, __func__);
    exit(EXIT_FAILURE);
  }

  new_node->word[0] = '\0';
  new_node->next = NULL;
  return new_node;
}
void free_nodes(void)
{
  Node *next = NULL;
  for (Node *n = line; n; n = next) {
    next = n->next;
    free(n);
  }
}
void clear_line(void)
{
  free_nodes();
  line = NULL;
  tail = NULL;
  line_len = 0;
  num_words = 0;
}

void add_word(const char *word)
{
  if (num_words == 0) {
    line = create();
    tail = line;
  } else {
    tail->next = create();
    tail = tail->next;
  }

  strcpy(tail->word, word);
  line_len += strlen(word);
  num_words++;
}

int space_remaining(void)
{
  return MAX_LINE_LEN - (line_len  + num_words - 1);
}

void write_line(void)
{
  int padding, gaps_needed, extra_spaces, spaces_to_insert, i;

  extra_spaces = space_remaining();
  for (Node *n = line; n; n = n->next) {
    printf("%s", n->word);
    if (n->next) {
      /* each gap between 2 words could have more than 1 space */
      gaps_needed = num_words - 1;
      padding = extra_spaces / gaps_needed;
      spaces_to_insert = 1 + padding;

      for (i = 1; i <= spaces_to_insert; i++)
        putchar(' ');
      extra_spaces -= padding;
      num_words--;
    }
  }
  putchar('\n');
}

void flush_line(void)
{
  if (line_len > 0) {
    for (Node *n = line; n; n = n->next) {
      printf("%s", n->word);
      if (n->next)
        putchar(' ');
    }
    putchar('\n');
  }
  free_nodes();
}
