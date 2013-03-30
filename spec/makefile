PREFIX = ../
include $(PREFIX)make/env.mk
SPECS       = $(filter-out ./parts-spec.c ./part-spec.c, $(shell find . -name '*-spec.c'))
# for lib/foo.c and spec/foo-spec.c, this will be 'foo'
BASE_NAMES  = $(notdir $(SPECS:-spec.c=))

COMPILE = $(CC) -c $(CFLAGS) $< -o $@
LINK = $(LD) $^ -o $@

all: $(SPECS:.c=) parts-spec  part-spec
	@for test in $(^); do echo $$test; ./$$test; done

parts-spec: parts-spec.o $(LIBS)/parts.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

parts-spec.o: parts-spec.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/error.h $(INCS)/test_runner.h
	$(COMPILE)

part-spec: part-spec.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

part-spec.o: part-spec.c $(INCS)/part.h $(INCS)/error.h $(INCS)/test_runner.h
	$(COMPILE)

# For each executable spec/foo-spec
# # check if spec/foo-spec.o or the corresponding lib/foo.o has changed
#
# command line should only be: "gcc foo-spec.o ../lib/foo.o -o foo-spec"
$(BASE_NAMES:=-spec) : %-spec : %-spec.o $(LIBS)/%.o
	$(LINK)

# For each obj spec/foo-spec.o
    # check if the corresponding spec/foo-spec.c or the test runner has changed
$(SPECS:.c=.o) : %.o : %.c $(INCS)/test_runner.h
	$(COMPILE)

# We end up here, in the lib/makefile, when lib/foo.c or include/foo.h has changed
include $(LIBS)/makefile
include $(PREFIX)make/clean.mk
