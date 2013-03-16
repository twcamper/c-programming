# tested with GNU make 3.81
include make/env.mk
#### Don't build source in directories with their own makefiles ###
#### or the example programs from the textbook ###
MF_DIRS     = $(dir $(shell find . -type f -name 'makefile'))
SELF_MAKERS = $(foreach mf_dir, $(MF_DIRS), $(wildcard $(mf_dir)*.c))
EXCLUDE     = $(shell find ./src -name '*.c') $(SELF_MAKERS)
INCS        = ./include

include make/generic.mk
all: $(EXECUTABLES)

include make/clean.mk
