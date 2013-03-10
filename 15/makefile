include ../make/env.mk

15.5.RPN-calculator: 15.5.RPN-calculator.o evaluate-rpn-expression.o stack.o
	$(LD) $^ -o $@

15.5.RPN-calculator.o: 15.5.RPN-calculator.c evaluate-rpn-expression.h stack.h
	$(CC) -c $(CFLAGS) $<

stack.o evaluate-rpn-expression.o: %.o : %.c %.h
	$(CC) -c $(CFLAGS) $<

include ../make/clean.mk
