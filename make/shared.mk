CSTD := -std=c++14
CFLAGS = -Wall $(CSTD) $(CMDCFLAGS)

-include $(OBJS:.o=.d)


obj/%.o: %.cpp
	mkdir -p obj
	$(CC) $(CFLAGS) -fPIC -c -o $@ -Wall -I$(TOP)/include $(LOCAL_INCLUDE) $<


obj/%.d: %.cpp
	mkdir -p obj
	$(CC) $(CSTD) -M -MT $(@:.d=.o) -MF $@ -I$(TOP)/include $(LOCAL_INCLUDE) $<

$(SLIB): $(SOBJS)
	mkdir -p $(@D)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ -lstdc++

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

