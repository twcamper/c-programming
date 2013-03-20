PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE =
include $(PREFIX)make/generic.mk

all: $(EXECUTABLES)

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@


include $(PREFIX)make/clean.mk
include $(LIBS)/makefile
