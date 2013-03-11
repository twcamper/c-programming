include ../make/env.mk

15.5.RPN-calculator: 15.5.RPN-calculator.o tokenize.o stack.o
	$(LD) $^ -o $@

15.5.RPN-calculator.o: 15.5.RPN-calculator.c tokenize.h stack.h
	$(CC) -c $(CFLAGS) $<

stack.o tokenize.o: %.o : %.c %.h
	$(CC) -c $(CFLAGS) $<

include ../make/clean.mk
