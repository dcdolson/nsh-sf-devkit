TOP := ..

DIRS := \
    Demux \
    HealthEcho \
    Interfaces \
    NetInterfaceFactory \
    PacketSocket \
    Scheduler \
    Vpp \

ifeq ($(DPDK_INCLUDE),)
DIRS += \
    StubDpdk
else
DIRS += \
    Dpdk
endif

all: dirs

include $(TOP)/make/macros.mk

