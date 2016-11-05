TOP := ../..

OBJS := $(addprefix obj/, \
    main.o \
    PacketCounter.o \
    Options.o \
    )

LIBS :=  \
    PacketSocket \
    Demux \
    HealthEcho \
    Interfaces

STDLIBS := stdc++

PROG := bin/count

all: $(PROG)

$(PROG): $(OBJS) $(addsuffix .a,$(addprefix $(TOP)/lib/lib,$(LIBS)))
	mkdir -p bin
	$(CC) -o $@ $(OBJS) -L$(TOP)/lib $(addprefix -l,$(LIBS) $(STDLIBS))

clean::
	rm -f $(PROG)

include $(TOP)/make/macros.mk

