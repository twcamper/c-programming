include ../make/env.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: 15.1.justify 15.5.RPN-calculator

15.1.justify: 15.1.justify.o line.o word.o
	$(LINK)

15.1.justify.o: 15.1.justify.c line.h word.h
	$(COMPILE)

line.o word.o: %.o : %.c %.h
	$(COMPILE)

15.5.RPN-calculator: 15.5.RPN-calculator.o tokenize.o stack.o
	$(LINK)

15.5.RPN-calculator.o: 15.5.RPN-calculator.c tokenize.h stack.h
	$(COMPILE)

stack.o tokenize.o: %.o : %.c %.h
	$(COMPILE)

include ../make/clean.mk
