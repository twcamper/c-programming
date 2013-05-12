PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./22.7-rle.c \
					./generate-parts.c \
					./22.inventory.c \
					./parts-io-profiler.c \
					./22.9-merge-parts.c \
					./22.13-find-departure.c \
					./22.15-justify.c \
					./22.19-convert-line-endings.c

include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all: $(EXECUTABLES) \
	22.7-rle \
	generate-parts \
	22.inventory \
	parts-list-io-profiler \
	parts-array-io-profiler \
	part-structs-io-profiler \
	22.9-merge-parts \
	22.13-find-departure \
	22.13-find-departure-unbuffered \
	22.15-justify \
	dos2unix \
	unix2dos

dos2unix: dos2unix.o
	$(LINK)

dos2unix.o: 22.19-convert-line-endings.c
	$(COMPILE) -D DOS2UNIX -o $@

unix2dos: unix2dos.o
	$(LINK)

unix2dos.o: 22.19-convert-line-endings.c
	$(COMPILE) -D UNIX2DOS -o $@

22.15-justify: 22.15-justify.o $(LIBS)/line.o $(LIBS)/word.o $(LIBS)/error.o
	$(LINK)

22.15-justify.o: %.o: %.c $(INCS)/line.h $(INCS)/word.h $(INCS)/error.h
	$(COMPILE)

22.13-find-departure-unbuffered: 22.13-find-departure.o $(LIBS)/find-departure-unbuffered.o 
	$(LINK)

22.13-find-departure: 22.13-find-departure.o $(LIBS)/find-departure.o
	$(LINK)

22.13-find-departure.o: %.o: %.c $(INCS)/find-departure.h
	$(COMPILE)

22.9-merge-parts: 22.9-merge-parts.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

22.9-merge-parts.o: %.o: %.c $(INCS)/part-type.h $(INCS)/part.h $(INCS)/error.h
	$(COMPILE)

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

parts-list-io-profiler: parts-io-profiler.o $(LIBS)/parts.o $(LIBS)/parts-list.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

parts-array-io-profiler: parts-io-profiler.o $(LIBS)/parts.o $(LIBS)/parts-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

part-structs-io-profiler: parts-io-profiler.o $(LIBS)/parts.o $(LIBS)/part-structs-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

parts-io-profiler.o: %.o : %.c $(INCS)/parts.h $(INCS)/tokenize.h $(INCS)/part.h $(INCS)/error.h
	$(COMPILE)

22.7-rle: 22.7-rle.o $(LIBS)/error.o $(LIBS)/run-length-encoding.o
	$(LINK)

22.7-rle.o: %.o : %.c $(INCS)/error.h $(INCS)/run-length-encoding.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
