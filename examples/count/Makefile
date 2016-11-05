TOP := ../..

OBJS := $(addprefix obj/, \
    main.o \
    PacketCounter.o \
    )

DPDK_OBJS := $(addprefix obj/, \
    dpdk_main.o \
    PacketCounter.o \
    )

LIBS :=  \
    PacketSocket \
    Demux \
    HealthEcho \
    Interfaces

STDLIBS := stdc++ 

DPDKLIBS := Dpdk \
            dpdk

PROG := bin/count

DPDK_PROG := bin/dpdk_count

all: $(PROG) $(DPDK_PROG)

$(PROG): $(OBJS) $(addsuffix .a,$(addprefix $(TOP)/lib/lib,$(LIBS)))
	mkdir -p bin
	$(CC) -o $@ $(OBJS) -L$(TOP)/lib $(addprefix -l,$(LIBS) $(STDLIBS))

$(DPDK_PROG): $(DPDK_OBJS) $(addsuffix .a,$(addprefix $(TOP)/lib/lib,$(LIBS)))
	mkdir -p bin
	$(CC) -g -o $@ $(DPDK_OBJS) -L$(TOP)/lib $(addprefix -l,$(DPDKLIBS) $(LIBS) $(STDLIBS))
    

clean::
	rm -f $(PROG) $(DPDK_PROG)

include $(TOP)/make/macros.mk

