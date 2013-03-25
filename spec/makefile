PREFIX = ../
include $(PREFIX)make/env.mk
SPECS       = $(filter-out ./inventory-model-spec.c ./inventory-record-validation-spec.c, $(shell find . -name '*-spec.c'))
# for lib/foo.c and spec/foo-spec.c, this will be 'foo'
BASE_NAMES  = $(notdir $(SPECS:-spec.c=))

LINK = $(LD) $^ -o $@

all: $(SPECS:.c=) inventory-record-validation-spec inventory-model-spec
	@for test in $(^); do echo $$test; ./$$test; done

inventory-model-spec.o: inventory-model-spec.c $(INCS)/inventory-model.h $(INCS)/inventory-array.h $(INCS)/test_runner.h
	$(CC) -c $(CFLAGS) $< -o $@

inventory-model-spec: inventory-model-spec.o $(LIBS)/inventory-model.o $(LIBS)/inventory-array.o
	$(LINK)

# This guy exists because of the annoying warnings about INT overflow, the handling of which
# is what were testing.  Needs a custom rule because he doesn't fit the naming convention.
inventory-record-validation-spec: inventory-record-validation-spec.o $(LIBS)/inventory-model.o $(LIBS)/inventory-array.o 
	$(LINK)

inventory-record-validation-spec.o: inventory-record-validation-spec.c $(INCS)/inventory-model.h $(INCS)/inventory-array.h $(INCS)/test_runner.h
	$(CC) -c $(CFLAGS) $< -o $@

# For each executable spec/foo-spec
# # check if spec/foo-spec.o or the corresponding lib/foo.o has changed
#
# command line should only be: "gcc foo-spec.o ../lib/foo.o -o foo-spec"
$(BASE_NAMES:=-spec) : %-spec : %-spec.o $(LIBS)/%.o
	$(LINK)

# For each obj spec/foo-spec.o
    # check if the corresponding spec/foo-spec.c or the test runner has changed
$(SPECS:.c=.o) : %.o : %.c $(INCS)/test_runner.h
	$(CC) -c $(CFLAGS) $< -o $@

# We end up here, in the lib/makefile, when lib/foo.c or include/foo.h has changed
include $(LIBS)/makefile
include $(PREFIX)make/clean.mk
