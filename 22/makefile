PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./22.7-encode.c ./22.7-decode.c
include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: $(EXECUTABLES) 22.7-encode

22.7-encode: 22.7-encode.o $(LIBS)/error.o
	$(LINK)

22.7-encode.o: %.o : %.c $(INCS)/error.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
