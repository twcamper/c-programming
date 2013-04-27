PREFIX = ../
include $(PREFIX)make/env.mk
EXCLUDE     = ./bounded-queue-spec.c\
							./parts-spec.c\
							./parts-array-spec.c\
							./part-structs-array-spec.c\
							./parts-array-resize-spec.c\
							./part-spec.c\
							./global-queue-spec.c\
							./queue-spec.c\
							./parts-io-spec.c

SPECS       = $(filter-out $(EXCLUDE), $(shell find . -name '*-spec.c'))
# for lib/foo.c and spec/foo-spec.c, this will be 'foo'
BASE_NAMES  = $(notdir $(SPECS:-spec.c=))

COMPILE = $(CC) -c $(CFLAGS) $< -o $@
LINK = $(LD) $^ -o $@

all: $(SPECS:.c=)\
	parts-array-spec \
	global-queue-spec \
	bounded-queue-spec \
	part-structs-array-spec \
	parts-array-resize-spec \
	parts-list-spec \
	parts-io-spec \
	part-spec \
	queue-spec
	@time for test in $(^); do ./$$test; done

parts-io-spec: parts-io-spec.o $(LIBS)/part-structs-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK) -lssl -lcrypto

part-io-spec.o: parts-io-spec.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/part-type.h $(INCS)/error.h $(INCS)/test_runner.h
	$(COMPILE)

queue-spec: queue-spec.o $(LIBS)/queue.o $(LIBS)/error.o
	$(LINK)

queue-spec.o: queue-spec.c $(LIBS)/queue.c $(INCS)/queue.h $(INCS)/error.h
	$(COMPILE)

global-queue-spec: global-queue-spec.o $(LIBS)/global-queue.o $(LIBS)/error.o
	$(LINK)

global-queue-spec.o: global-queue-spec.c $(LIBS)/global-queue.c $(INCS)/global-queue.h $(INCS)/error.h
	$(COMPILE)

bounded-queue-spec: bounded-queue-spec.o $(LIBS)/bounded-queue.o $(LIBS)/error.o
	$(LINK)

bounded-queue-spec.o: bounded-queue-spec.c $(LIBS)/bounded-queue.c $(INCS)/global-queue.h $(INCS)/error.h
	$(COMPILE)

part-structs-array-spec: part-structs-array-spec.o $(LIBS)/parts.o $(LIBS)/part-structs-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK) -lssl -lcrypto

# NOTE: Just one test file for the array and the list implementations!!
part-structs-array-spec.o: parts-spec.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/part-type.h $(INCS)/error.h $(INCS)/test_runner.h
	$(COMPILE)

parts-array-spec: parts-array-spec.o $(LIBS)/parts.o $(LIBS)/parts-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK) -lssl -lcrypto

# NOTE: Just one test file for the array and the list implementations!!
parts-array-spec.o: parts-spec.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/part-type.h $(INCS)/error.h $(INCS)/test_runner.h
	$(COMPILE)

parts-list-spec: parts-list-spec.o $(LIBS)/parts.o $(LIBS)/parts-list.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK) -lssl -lcrypto

# NOTE: Just one test file for the array and the list implementations!!
parts-list-spec.o: parts-spec.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/part-type.h $(INCS)/error.h $(INCS)/test_runner.h
	$(COMPILE)

parts-array-resize-spec: parts-array-resize-spec.o $(LIBS)/parts.o $(LIBS)/parts-array.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK) -lssl -lcrypto

parts-array-resize-spec.o: parts-array-resize-spec.c $(INCS)/parts.h $(INCS)/part.h $(INCS)/part-type.h $(INCS)/error.h $(INCS)/test_runner.h
	$(COMPILE)

part-spec: part-spec.o $(LIBS)/part.o $(LIBS)/error.o
	$(LINK)

part-spec.o: part-spec.c $(INCS)/part.h $(INCS)/part-type.h $(INCS)/error.h $(INCS)/test_runner.h
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
