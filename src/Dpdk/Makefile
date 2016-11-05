TOP := ../..
LIB := $(TOP)/lib/libDpdk.a

all: $(LIB)

OBJS := $(addprefix obj/, \
    DpdkNetInterface.o \
    DpdkSetup.o \
    )

include $(TOP)/make/macros.mk

ifeq ($(DPDK_INCLUDE),)
$(error "Please define DPDK_INCLUDE environment variable")
endif

LOCAL_INCLUDE += \
    -I$(DPDK_INCLUDE) \


