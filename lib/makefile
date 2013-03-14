include ../make/env.mk

%.o : %.c $(INCS)/%.h
	$(CC) -I$(INCS) -c $(CFLAGS) $< -o $@
