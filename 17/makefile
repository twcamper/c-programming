PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./17.3-inventory.c
include $(PREFIX)make/generic.mk

all: $(EXECUTABLES) ./17.3-inventory

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

17.3-inventory: 17.3-inventory.o $(LIBS)/readline.o
	$(LINK)

17.3-inventory.o: 17.3-inventory.c $(INCS)/readline.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
