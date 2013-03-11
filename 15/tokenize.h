#ifndef TOKENIZE_H
#define TOKENIZE_H

#if !defined(__STDBOOL_H) && !defined(_STDBOOL_H_)
#include <stdbool.h>
#endif

#include <ctype.h>

void tokenize(char *string, char **tokens, int *token_count);
#endif
