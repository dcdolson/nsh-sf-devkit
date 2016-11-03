CFLAGS := -Wall -std=c++14
LDFLAGS := -lstdc++

-include $(OBJS:.o=.d)


obj/%.o: %.cpp
	mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ -Wall -I$(TOP)/include $(LOCAL_INCLUDE) $<


obj/%.d: %.cpp
	mkdir -p obj
	$(CC) -M -MT $(@:.d=.o) -MF $@ -I$(TOP)/include $(LOCAL_INCLUDE) $<



