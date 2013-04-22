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

################################################################################################################################################
#  Same as 16/16.inventory, except we use lib/parts-list.c instead of lib/parts-array.c
################################################################################################################################################
17.3-inventory: 17.3-inventory.o $(LIBS)/parts.o $(LIBS)/parts-list.o $(LIBS)/inventory-view.o $(LIBS)/part.o $(LIBS)/readline.o $(LIBS)/error.o
	$(LINK)

16 = $(PREFIX)16/
17.3-inventory.o: $(16)16.inventory.c $(INCS)/parts.h $(INCS)/inventory-view.h $(INCS)/part.h $(INCS)/part-type.h $(INCS)/readline.h $(INCS)/error.h
	$(COMPILE) -o $@

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
