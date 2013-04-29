PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./22.7-rle.c ./generate-parts.c ./22.inventory.c ./load-parts.c
include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: $(EXECUTABLES) 22.7-rle generate-parts 22.inventory load-parts

################################################################################################################################################
#  Same as 16/16.inventory, except we use lib/part-structs-array.c instead of lib/parts-array.c
################################################################################################################################################
22.inventory: 22.inventory.o $(LIBS)/parts.o $(LIBS)/part-structs-array.o $(LIBS)/inventory-view.o $(LIBS)/part.o $(LIBS)/readline.o $(LIBS)/error.o
	$(LINK)

16 = $(PREFIX)16/
22.inventory.o: $(16)16.inventory.c $(INCS)/parts.h $(INCS)/inventory-view.h $(INCS)/part.h $(INCS)/part-type.h $(INCS)/readline.h $(INCS)/error.h
	$(COMPILE) -o $@

generate-parts: generate-parts.o $(LIBS)/parts.o $(LIBS)/tokenize.o $(LIBS)/part-structs-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

generate-parts.o: %.o : %.c $(INCS)/parts.h $(INCS)/tokenize.h $(INCS)/part.h $(INCS)/error.h
	$(COMPILE)

load-parts: load-parts.o $(LIBS)/parts.o $(LIBS)/part-structs-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

load-parts.o: %.o : %.c $(INCS)/parts.h $(INCS)/tokenize.h $(INCS)/part.h $(INCS)/error.h
	$(COMPILE)

22.7-rle: 22.7-rle.o $(LIBS)/error.o $(LIBS)/run-length-encoding.o
	$(LINK)

22.7-rle.o: %.o : %.c $(INCS)/error.h $(INCS)/run-length-encoding.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
