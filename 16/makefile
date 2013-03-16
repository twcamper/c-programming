include ../make/env.mk
EXCLUDE = ./16.1.5-6.c ./16.1.7.fraction.c ./16.3.10.rectangle-spec.c
include ../make/generic.mk

all: 16.1.5-6 $(EXECUTABLES) 16.1.7.fraction ./16.3.10.rectangle-spec

COMPILE = $(CC) -c -I$(INCS) $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

16.3.10.rectangle-spec: 16.3.10.rectangle-spec.o $(LIBS)/rectangle.o
	$(LINK)

16.3.10.rectangle-spec.o: 16.3.10.rectangle-spec.c $(INCS)/rectangle.h
	$(COMPILE)

16.1.7.fraction: 16.1.7.fraction.o $(LIBS)/error.o
	$(LINK)

16.1.7.fraction.o: 16.1.7.fraction.c $(INCS)/error.h
	$(COMPILE)

16.1.5-6: 16.1.5-6.o $(LIBS)/time_helper.o
	$(LINK)

16.1.5-6.o: 16.1.5-6.c $(INCS)/time_helper.h
	$(COMPILE)

include ../make/clean.mk
include $(LIBS)/makefile
