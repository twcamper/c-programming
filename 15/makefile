PREFIX = ../

include $(PREFIX)make/env.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: 15.1.justify 15.3.qsort 15.5.RPN-calculator

15.1.justify: 15.1.justify.o $(LIBS)/line.o $(LIBS)/word.o
	$(LINK)

15.1.justify.o: 15.1.justify.c $(INCS)/line.h $(INCS)/word.h
	$(COMPILE)

15.3.qsort: 15.3.qsort.o quicksort.o
	$(LINK)

15.3.qsort.o: 15.3.qsort.c quicksort.h
	$(COMPILE)

quicksort.o: %.o : %.c %.h
	$(COMPILE)

15.5.RPN-calculator: 15.5.RPN-calculator.o $(LIBS)/tokenize.o stack.o
	$(LINK)

15.5.RPN-calculator.o: 15.5.RPN-calculator.c $(INCS)/tokenize.h stack.h
	$(COMPILE)

stack.o tokenize.o: %.o : %.c %.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
