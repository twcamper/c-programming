PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./19.3a.bounded-queue.c ./19.1-nester-tester.c ./19.2-RPN-calculator.c ./19.5-queue-client.c
include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: $(EXECUTABLES) 19.3a.bounded-queue 19.1-nester-tester 19.2-RPN-calculator 19.5-queue-client

SRC = $(PREFIX)src
15 = $(PREFIX)15

19.5-queue-client: 19.5-queue-client.o $(LIBS)/queue.o $(LIBS)/error.o
	$(LINK)

19.5-queue-client.o: %.o : %.c $(INCS)/queue.h $(INCS)/error.h
	$(COMPILE)

19.1-nester-tester: 19.1-nester-tester.o stackADT3.o
	$(LINK)

19.2-RPN-calculator: 19.2-RPN-calculator.o stackADT3.o tokenize.o
	$(LINK)

stackADT3.o: $(SRC)/stackADT3.c $(SRC)/stackADT.h
	$(COMPILE) -I$(SRC)

tokenize.o: $(15)/tokenize.c $(15)/tokenize.h
	$(COMPILE) -I$(15)

19.3a.bounded-queue: 19.3a.bounded-queue.o $(LIBS)/bounded-queue.o $(LIBS)/error.o
	$(LINK)

19.3a.bounded-queue.o: %.o : %.c $(INCS)/global-queue.h $(INCS)/error.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
