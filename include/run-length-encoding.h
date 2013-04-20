#ifndef RUN_LENGTH_ENCODING_H
#define RUN_LENGTH_ENCODING_H
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "error.h"

void encode_rle(FILE *, FILE *);
void decode_rle(FILE *, FILE *);
bool is_rle_file(char *);
char *build_output_file_name(char *);
#endif
