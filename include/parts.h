#ifndef PARTS_H
#define PARTS_H
#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  #define _BSD_SOURCE 1
#endif
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <openssl/md5.h>
#include <sys/stat.h>
#include "part.h"
#include "error.h"

typedef struct parts_type *Parts;

Parts new_db(size_t);
char *checksum(Parts);
void destroy_db(Parts);
int insert_part(Parts, Part);
int delete_part(Parts, PartNumber);
Part find_part(Parts, PartNumber);
Part approximate_part(Parts, PartNumber);
void load(Parts);
int dump(char *, Parts);
int flush_to_disk(char *, Parts);
Parts restore(char *);
void iterate(Parts, void (*)(Part));
void iterate_by_page(Parts, size_t, void (*)(Part), int (*)(void));
size_t size(Parts);
Part last_part(Parts);
#endif
