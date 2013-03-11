#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#if !defined(__STDBOOL_H) && !defined(_STDHOOL_H_)
#include <stdbool.h>
#endif

#include <stdlib.h>

extern int stack[];
extern int top;

void empty_stack(void);
bool is_empty(void);
bool is_full(void);
void push(int operand);
int pop(void);
void exit_stack_overflow(void);
void exit_stack_underflow(void);
#endif
