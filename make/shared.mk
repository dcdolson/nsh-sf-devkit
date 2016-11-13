CSTD := -std=c++14
CFLAGS = -Wall $(CSTD) $(CMDCFLAGS)

-include $(OBJS:.o=.d)

$(SLIB): $(SOBJS) $(addsuffix .a,$(addprefix $(TOP)/lib/lib,$(SLIB_DEPS)))
	mkdir -p $(@D)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ -lstdc++ -L$(TOP)/lib $(addprefix -l,$(SLIB_DEPS))

ifneq ($(SLIB),)
clean::
	-rm -f $(SLIB)
endif

ifneq ($(SOBJS),)
clean::
	-rm -f $(SOBJS)
	-rm -f $(SOBJS:.o=.d)
endif

.PHONY: dirs
define build_dir
dirs::
	$(MAKE) -C $1

clean::
	$(MAKE) -C $1 clean
endef

$(foreach d,$(DIRS),$(eval $(call build_dir,$d)))

