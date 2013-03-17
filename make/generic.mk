ALL_SRC     = $(shell find . -name '*.c' |  tr '\n' ' ')

# includer must set EXCLUDE list before the include line
SRCS        = $(filter-out $(EXCLUDE), $(ALL_SRC))
OBJECTS     = $(SRCS:.c=.o)
EXECUTABLES = $(SRCS:.c=)

warn:
	@echo You probably mean "'all'"

#### Build all executable targets, using a 'Static Pattern Rule' (GNU make manual, 4.11) ####
$(EXECUTABLES) : % : %.o
	$(LD) $< -o $@

#### compiled object files ####
$(OBJECTS) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
