TOP := ../..

SLIB := $(TOP)/lib/libexample_count.so

SOBJS := $(addprefix obj/, \
    PacketCounter.o \
    shared_main.o \
    )

OBJS := $(addprefix obj/, \
    main.o \
    PacketCounter.o \
    )

SLIB_DEPS :=  \
    Demux \
    HealthEcho \
    Interfaces \
    vpp \

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

all: $(PROG) $(SLIB)

$(PROG): $(OBJS) $(addsuffix .a,$(addprefix $(TOP)/lib/lib,$(LIBS)))
	mkdir -p bin
	$(CC) -o $@ $(OBJS) -L$(TOP)/lib $(addprefix -l,$(LIBS) $(LIBS) $(STDLIBS))

clean::
	rm -f $(PROG)

include $(TOP)/make/macros.mk
include $(TOP)/make/shared.mk

