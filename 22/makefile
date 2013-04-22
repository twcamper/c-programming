PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./22.7-rle.c ./generate-parts.c
include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: $(EXECUTABLES) 22.7-rle generate-parts

generate-parts: generate-parts.o $(LIBS)/parts.o $(LIBS)/part-structs-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

generate-parts.o: %.o : %.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/error.h
	$(COMPILE)

22.7-rle: 22.7-rle.o $(LIBS)/error.o $(LIBS)/run-length-encoding.o
	$(LINK)

22.7-rle.o: %.o : %.c $(INCS)/error.h $(INCS)/run-length-encoding.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
