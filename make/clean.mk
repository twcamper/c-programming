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

