#ifndef PARTS_H
#define PARTS_H
#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  /* for off_t.
   * including sys/types.h is a frowned upon hack,
   * but I can't figure out the feature macro combination
   * to make it work.
   */
  #include <sys/types.h>
#endif
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "part.h"
#include "error.h"

typedef struct parts_type *Parts;

Parts new_db(size_t);
void destroy_db(Parts);
int insert_part(Parts, Part);
int delete_part(Parts, PartNumber);
Part find_part(Parts, PartNumber);
Part approximate_part(Parts, PartNumber);
void load(Parts);
int dump(char *, Parts);
int flush_to_disk(char *, Parts);
Parts read_parts_file(char *infile, int(*process_records)(Parts, FILE *, off_t));
Parts load_parts(char *);
void iterate(Parts, void (*)(Part));
void iterate_by_page(Parts, size_t, void (*)(Part), int (*)(void));
size_t size(Parts);
Part last_part(Parts);
#endif
