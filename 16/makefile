include ../make/env.mk
EXCLUDE = ./16.1.5-6.c
include ../make/generic.mk

all: 16.1.5-6 $(EXECUTABLES)

COMPILE = $(CC) -c -I$(INCS) $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

16.1.5-6: 16.1.5-6.o $(LIBS)/time_helper.o
	$(LINK)

16.1.5-6.o: 16.1.5-6.c $(INCS)/time_helper.h
	$(COMPILE)

include ../make/clean.mk
include $(LIBS)/makefile
