# tested with GNU make 3.81
SHELL   = /usr/bin/env sh
DBGFLAGS = -g3
CC = clang
LD = clang

# Flag -Wextra replaces -W in newer gcc's.  Use -W if you have an old version of gcc and get an arg error.
#
# Flag -O (optimize) is needed by clang so it will inline functions that
# are also extern (e.g., sqrt() in math.h).  GCC does that by default.
# We get linker 'undefined reference' errors if such functions aren't inlined
#
# 'override' alows us to prepend from the command line (GNU make manual, 6.7)
override CFLAGS += -O $(DBGFLAGS) -Wall -Wextra -pedantic -std=c99

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

.PHONY : clean clean-obj clean-bin

clean: clean-obj clean-archives clean-bin

XARGS_RM = xargs rm -fv
CLEAN_PATH = ./$(CLEAN)

clean-obj:
	@find $(CLEAN_PATH) -name '*.o' | $(XARGS_RM)

clean-archives:
	@find $(CLEAN_PATH) -name '*.a' | $(XARGS_RM)
	@find $(CLEAN_PATH) -name '*.so' | $(XARGS_RM)

clean-bin:
	@find $(CLEAN_PATH) -perm +111 -type f | grep -vE '\.git' | $(XARGS_RM)
