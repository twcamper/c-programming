PREFIX = ../
include $(PREFIX)make/env.mk
SPECS       = $(filter-out ./global-bounded-queue-spec.c ./parts-spec.c ./parts-array-resize-spec.c ./part-spec.c, $(shell find . -name '*-spec.c'))
# for lib/foo.c and spec/foo-spec.c, this will be 'foo'
BASE_NAMES  = $(notdir $(SPECS:-spec.c=))

COMPILE = $(CC) -c $(CFLAGS) $< -o $@
LINK = $(LD) $^ -o $@

all: $(SPECS:.c=) parts-array-spec global-bounded-queue-spec parts-array-resize-spec parts-list-spec part-spec
	@for test in $(^); do echo $$test; ./$$test; done

global-bounded-queue-spec: global-bounded-queue-spec.o $(LIBS)/global-bounded-queue.o
	$(LINK)

global-bounded-queue-spec.o: global-bounded-queue-spec.c $(LIBS)/global-bounded-queue.c $(INCS)/global-queue.h
	$(COMPILE)

parts-array-spec: parts-array-spec.o $(LIBS)/parts.o $(LIBS)/parts-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

# NOTE: Just one test file for the array and the list implementations!!
parts-array-spec.o: parts-spec.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/error.h $(INCS)/test_runner.h
	$(COMPILE)

parts-list-spec: parts-list-spec.o $(LIBS)/parts.o $(LIBS)/parts-list.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

# NOTE: Just one test file for the array and the list implementations!!
parts-list-spec.o: parts-spec.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/error.h $(INCS)/test_runner.h
	$(COMPILE)

parts-array-resize-spec: parts-array-resize-spec.o $(LIBS)/parts.o $(LIBS)/parts-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

parts-array-resize-spec.o: parts-array-resize-spec.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/error.h $(INCS)/test_runner.h
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
