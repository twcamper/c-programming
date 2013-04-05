PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./19.3a.global-bounded-queue.c
include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: $(EXECUTABLES) 19.3a.global-bounded-queue

19.3a.global-bounded-queue: 19.3a.global-bounded-queue.o $(LIBS)/global-bounded-queue.o
	$(LINK)

19.3a.global-bounded-queue.o: %.o : %.c $(INCS)/global-queue.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
