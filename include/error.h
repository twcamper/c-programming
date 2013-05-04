#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void invocation_error(char *program, char *usage);
void memory_error(char *file, unsigned int line, const char *func);
void print_error(char *, char *);
void exit_error(char *, char *);
int is_file_name_error(int);
