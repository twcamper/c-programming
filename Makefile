# tested with GNU make 3.81
include make/env.mk
#### targets and prerequisites ####
TEMP        = $(shell find . -name '*.c' |  tr '\n' ' ')
#### Don't build source in directories with their own makefiles ###
#### or the example programs from the textbook ###
MF_DIRS     = $(dir $(shell find . -type f -name 'makefile'))
SELF_MAKERS = $(foreach mf_dir, $(MF_DIRS), $(wildcard $(mf_dir)*))
SRCS        = $(filter-out ./src%.c $(SELF_MAKERS), $(TEMP))

OBJECTS     = $(SRCS:.c=.o)
EXECUTABLES = $(SRCS:.c=)

#### One target per *.c source file found above ####
all: $(EXECUTABLES)

#### Build all executable targets, using a 'Static Pattern Rule' (GNU make manual, 4.11) ####
$(EXECUTABLES) : % : %.o
	$(LD) $< -o $@

#### compiled object files ####
$(OBJECTS) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

include make/clean.mk
