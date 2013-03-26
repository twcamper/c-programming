PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./17.3-inventory.c ./17.4-line.c ./17.5-sort-words.c
include $(PREFIX)make/generic.mk

all: $(EXECUTABLES) ./17.3-inventory ./17.4-justify ./17.5-sort-words

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

17.5-sort-words: 17.5-sort-words.o $(LIBS)/readline.o $(LIBS)/error.o
	$(LINK)

17.5-sort-words.o: 17.5-sort-words.c $(INCS)/readline.h $(INCS)/error.h
	$(COMPILE)

17.4-justify: 17.4-justify.o 17.4-line.o $(LIBS)/word.o
	$(LINK)

15 = $(PREFIX)15/
17.4-justify.o: $(15)15.1.justify.c $(INCS)/line.h $(INCS)/word.h
	$(COMPILE) -o $@

17.4-line.o: 17.4-line.c $(INCS)/line.h
	$(COMPILE)

17.3-inventory: 17.3-inventory.o $(LIBS)/readline.o
	$(LINK)

17.3-inventory.o: 17.3-inventory.c $(INCS)/readline.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
