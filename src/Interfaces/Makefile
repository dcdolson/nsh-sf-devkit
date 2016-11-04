TOP := ../..
LIB := ../../lib/libInterfaces.a

all: $(LIB)

OBJS := $(addprefix obj/, \
    NetInterface.o \
    PacketSocket.o \
    )

$(LIB): $(OBJS)
	mkdir -p $(@D)
	$(AR) r $@ $^

include $(TOP)/make/macros.mk

