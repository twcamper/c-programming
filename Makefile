# tested with GNU make 3.81
SHELL   = /usr/bin/env sh
CC      = gcc
# flag -Wextra replaces -W in newer gcc's.  Use -W if you have an old version of gcc and get an arg error.
CFLAGS  = -g3 -gdwarf-4 -Wall -Wextra -pedantic -std=c99
LD      = gcc

#### targets and prerequisites ####
SRCS        = $(shell find . -name '*.c' |  tr '\n' ' ')
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

# GNU xargs
XARGS_RM = xargs --no-run-if-empty rm -fv

clean-obj:
	@find . -name '*.o' | $(XARGS_RM)

clean-archives:
	@find . -name '*.a' | $(XARGS_RM)
	@find . -name '*.so' | $(XARGS_RM)

clean-bin:
	@find . -perm +111 -type f | grep -v \.git | $(XARGS_RM)
