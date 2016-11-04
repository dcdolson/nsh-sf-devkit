CFLAGS := -Wall -std=c++14
LDFLAGS := -lstdc++

-include $(OBJS:.o=.d)


obj/%.o: %.cpp
	mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ -Wall -I$(TOP)/include $(LOCAL_INCLUDE) $<


obj/%.d: %.cpp
	mkdir -p obj
	$(CC) -M -MT $(@:.d=.o) -MF $@ -I$(TOP)/include $(LOCAL_INCLUDE) $<

$(LIB): $(OBJS)
	mkdir -p $(@D)
	$(AR) r $@ $^

ifneq ($(LIB),)
clean::
	-rm -f $(LIB)
endif

ifneq ($(OBJS),)
clean::
	-rm -f $(OBJS)
	-rm -f $(OBJS:.o=.d)
endif

.PHONY: dirs
define build_dir
dirs::
	$(MAKE) -C $1

clean::
	$(MAKE) -C $1 clean
endef

$(foreach d,$(DIRS),$(eval $(call build_dir,$d)))

