PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./19.3a.global-bounded-queue.c ./19.1-nester-tester.c
include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: $(EXECUTABLES) 19.3a.global-bounded-queue 19.1-nester-tester

SRC = $(PREFIX)src
19.1-nester-tester: 19.1-nester-tester.o stackADT3.o
	$(LINK)

stackADT3.o: $(SRC)/stackADT3.c $(SRC)/stackADT.h
	$(COMPILE) -I$(SRC)

19.3a.global-bounded-queue: 19.3a.global-bounded-queue.o $(LIBS)/global-bounded-queue.o
	$(LINK)

19.3a.global-bounded-queue.o: %.o : %.c $(INCS)/global-queue.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
