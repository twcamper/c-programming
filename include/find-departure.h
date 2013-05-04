#ifndef FIND_DEPARTURE_H
#define FIND_DEPARTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>

#define DATA_ERROR(f, l, s)                                               \
        do {                                                              \
          fprintf(stderr, "Invalid data  %s:%ld  '%s'\n", (f), (l), (s)); \
          data_error = true;                                              \
        } while (0)

#define TIME_STR_SIZE 6
#define FILE_PATH "data/flights.txt"

void find_closest_flight(int, int *, int *);
void print_am_pm(int);
int get_valid_input(void);
int to_minutes(char *);
bool is_format_valid(char *);
void convert(char *, int *, int *);

#endif
