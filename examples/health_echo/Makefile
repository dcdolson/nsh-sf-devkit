TOP := ../..

OBJS := $(addprefix obj/, \
    main.o \
    )

LIBS :=  \
    NetInterfaceFactory \
    PacketSocket \
    Dpdk \
    HealthEcho \
    Interfaces \
    Scheduler \

STDLIBS := stdc++

ifneq ($(DPDK_INCLUDE),)
STDLIBS += \
    dpdk
endif

PROG := bin/health_echo

all: $(PROG)

$(PROG): $(OBJS) $(addsuffix .a,$(addprefix $(TOP)/lib/lib,$(LIBS)))
	mkdir -p bin
	$(CC) -o $@ $(OBJS) -L$(TOP)/lib $(addprefix -l,$(LIBS) $(STDLIBS))

clean::
	rm -f $(PROG)

include ../../make/macros.mk

