PREFIX = ../
include $(PREFIX)make/env.mk
SPECS       = $(shell find . -name '*-spec.c')
SPEC_LIBS   = $(patsubst ./%,$(LIBS)/%,$(SPECS:-spec.c=.o))
SPEC_HEADERS = $(patsubst ./%,$(INCS)/%,$(SPECS:-spec.c=.h)) $(INCS)/test_runner.h

all: $(SPECS:.c=)
	@for test in $(^); do echo $$test; ./$$test; done

$(SPECS:.c=) : % : %.o $(SPEC_LIBS)
	$(LD) $^ -o $@

$(SPECS:.c=.o) : %.o : %.c $(SPEC_HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

include $(LIBS)/makefile
include $(PREFIX)make/clean.mk
