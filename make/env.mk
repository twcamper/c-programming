SHELL    = /usr/bin/env sh
DBGFLAGS = -g3 -gdwarf-2
OFLAGS   = -O
CC       = clang
LD       = clang
INCS     = ../include
LIBS     = ../lib

# Flag -Wextra replaces -W in newer gcc's.  Use -W if you have an old version of gcc and get an arg error.
#
# Flag -O (optimize) is needed by clang so it will inline functions that
# are also extern (e.g., sqrt() in math.h).  GCC does that by default.
# We get linker 'undefined reference' errors if such functions aren't inlined
#
# 'override' alows us to prepend from the command line (GNU make manual, 6.7)
override CFLAGS += $(OFLAGS) $(DBGFLAGS) -Wall -Wextra -pedantic -std=c99
