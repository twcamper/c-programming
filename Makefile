# tested with GNU make 3.81
PREFIX      = ./
include make/env.mk
#### Don't build source in directories with their own makefiles ###
#### or the example programs from the textbook ###
MF_DIRS     = $(dir $(shell find . -type f -name 'makefile'))
SELF_MAKERS = $(foreach mf_dir, $(MF_DIRS), $(wildcard $(mf_dir)*.c))
SPECS       = $(shell find ./spec -name '*-spec.c')
EXCLUDE     = $(shell find ./src -name '*.c') $(SELF_MAKERS) $(SPECS)
SPEC_LIBS   = $(patsubst ./spec%,$(LIBS)%,$(SPECS:-spec.c=.o))
SPEC_HEADERS = $(patsubst ./spec%,$(INCS)%,$(SPECS:-spec.c=.h))

include make/generic.mk
all: $(EXECUTABLES)

spec: $(SPECS:.c=)
	@for test in $(^); do ./$$test; done

$(SPECS:.c=) : % : %.o $(SPEC_LIBS)
	$(LD) $^ -o $@

$(SPECS:.c=.o) : %.o : %.c $(SPEC_HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

include make/clean.mk
include $(LIBS)/makefile
