SHELL    = /usr/bin/env sh
DBGFLAGS = -g3 -gdwarf-2
#
# Use flag -O (optimize) to make clang inline functions that
# are also extern (e.g., sqrt() in math.h).  GCC does that by default.
# We get linker 'undefined reference' errors if such functions aren't inlined
OFLAGS   =
CC       = clang
LD       = clang
INCS     = ../include
LIBS     = ../lib

# Flag -Wextra replaces -W in newer gcc's.  Use -W if you have an old version of gcc and get an arg error.
#
# 'override' alows us to prepend from the command line (GNU make manual, 6.7)
override CFLAGS += $(OFLAGS) $(DBGFLAGS) -Wall -Wextra -pedantic -std=c99
