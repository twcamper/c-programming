PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./queue.c
include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: $(EXECUTABLES) queue

queue: queue.o
	$(LINK)

queue.o: queue.c ./queue.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
