PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./16.1.5-6.c ./16.1.7.fraction.c ./16.1.country-codes.c
include $(PREFIX)make/generic.mk

all: 16.1.5-6 $(EXECUTABLES) 16.1.7.fraction ./16.1.country-codes

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

16.1.country-codes: 16.1.country-codes.o $(LIBS)/error.o
	$(LINK)

16.1.country-codes.o: 16.1.country-codes.c $(INCS)/error.h
	$(COMPILE)

16.1.7.fraction: 16.1.7.fraction.o $(LIBS)/error.o
	$(LINK)

16.1.7.fraction.o: 16.1.7.fraction.c $(INCS)/error.h
	$(COMPILE)

16.1.5-6: 16.1.5-6.o $(LIBS)/time_helper.o
	$(LINK)

16.1.5-6.o: 16.1.5-6.c $(INCS)/time_helper.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
