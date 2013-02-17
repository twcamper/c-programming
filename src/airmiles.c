/*********************************************************
 * From C PROGRAMMING: A MODERN APPROACH, Second Edition *
 * By K. N. King                                         *
 * Copyright (c) 2008, 1996 W. W. Norton & Company, Inc. *
 * All rights reserved.                                  *
 * This program may be freely distributed for class use, *
 * provided that this copyright notice is retained.      *
 *********************************************************/

/* airmiles.c (Chapter 26, page 690) */
/* Determines air mileage from New York to other cities */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct city_info {
  char *city;
  int miles;
};

int compare_cities(const void *key_ptr,
                   const void *element_ptr);

int main(void)
{
  char city_name[81];
  struct city_info *ptr;
  const struct city_info mileage[] =
    {{"Berlin",         3965}, {"Buenos Aires", 5297},
     {"Cairo",          5602}, {"Calcutta",     7918},
     {"Cape Town",      7764}, {"Caracas",      2132},
     {"Chicago",         713}, {"Hong Kong",    8054},
     {"Honolulu",       4964}, {"Istanbul",     4975},
     {"Lisbon",         3364}, {"London",       3458},
     {"Los Angeles",    2451}, {"Manila",       8498},
     {"Mexico City",    2094}, {"Montreal",      320},
     {"Moscow",         4665}, {"Paris",        3624},
     {"Rio de Janeiro", 4817}, {"Rome",         4281},
     {"San Francisco",  2571}, {"Shanghai",     7371},
     {"Stockholm",      3924}, {"Sydney",       9933},
     {"Tokyo",          6740}, {"Warsaw",       4344},
     {"Washington",      205}};

  printf("Enter city name: ");
  scanf("%80[^\n]", city_name);
  ptr = bsearch(city_name, mileage,
                sizeof(mileage) / sizeof(mileage[0]),
                sizeof(mileage[0]), compare_cities);
  if (ptr != NULL)
    printf("%s is %d miles from New York City.\n",
           city_name, ptr->miles);
  else
    printf("%s wasn't found.\n", city_name);

  return 0;
}

int compare_cities(const void *key_ptr,
                   const void *element_ptr)
{
  return strcmp((char *) key_ptr,
                ((struct city_info *) element_ptr)->city);
}
