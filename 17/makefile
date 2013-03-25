PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./17.3-inventory.c ./17.4-line.c
include $(PREFIX)make/generic.mk

all: $(EXECUTABLES) ./17.3-inventory ./17.4-justify

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

17.4-justify: 17.4-justify.o 17.4-line.o word.o
	$(LINK)

15 = $(PREFIX)15/
17.4-justify.o: $(15)15.1.justify.c $(15)line.h $(15)word.h
	$(COMPILE) -o $@  -I$(15)

17.4-line.o: 17.4-line.c $(15)line.h
	$(COMPILE) -I$(15)

word.o: $(15)word.c $(15)word.h
	$(COMPILE) -I$(15)

17.3-inventory: 17.3-inventory.o $(LIBS)/readline.o
	$(LINK)

17.3-inventory.o: 17.3-inventory.c $(INCS)/readline.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
