#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

size_t tokenize(char *string, char **tokens);
#endif
