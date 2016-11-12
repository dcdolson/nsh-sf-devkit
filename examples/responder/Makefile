TOP := ../..

OBJS := $(addprefix obj/, \
    main.o \
    Responder.o \
    )

LIBS :=  \
    NetInterfaceFactory \
    PacketSocket \
    Dpdk \
    Demux \
    HealthEcho \
    Interfaces \
    Scheduler \
    cksum \

STDLIBS := stdc++

ifneq ($(DPDK_INCLUDE),)
STDLIBS += \
    dpdk
endif

PROG := bin/responder

all: $(PROG)

$(PROG): $(OBJS) $(addsuffix .a,$(addprefix $(TOP)/lib/lib,$(LIBS)))
	mkdir -p bin
	$(CC) -o $@ $(OBJS) -L$(TOP)/lib $(addprefix -l,$(LIBS) $(LIBS) $(STDLIBS))

clean::
	rm -f $(PROG)

include $(TOP)/make/macros.mk

