TOP := ../..

OBJS := $(addprefix obj/, \
    main.o \
    PacketCounter.o \
    )

LIBS :=  \
    NetInterfaceFactory \
    PacketSocket \
    Dpdk \
    Demux \
    HealthEcho \
    Interfaces \
    Scheduler \

STDLIBS := stdc++

ifneq ($(DPDK_INCLUDE),)
STDLIBS += \
    dpdk
endif

PROG := bin/count

all: $(PROG)

$(PROG): $(OBJS) $(addsuffix .a,$(addprefix $(TOP)/lib/lib,$(LIBS)))
	mkdir -p bin
	$(CC) -o $@ $(OBJS) -L$(TOP)/lib $(addprefix -l,$(LIBS) $(LIBS) $(STDLIBS))

clean::
	rm -f $(PROG)

include $(TOP)/make/macros.mk

