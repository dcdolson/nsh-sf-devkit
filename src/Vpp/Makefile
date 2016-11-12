TOP := ../..

SLIB := $(TOP)/lib/vpp.so

SOBJS := $(addprefix obj/, \
    PacketCounter.o \
    VppIntegration.o \
    VppNetInterface.o \
    )

include $(TOP)/make/shared.mk

ifeq ($(VPP_INCLUDE),)
$(error "Please define VPP_INCLUDE environment variable")
endif

LOCAL_INCLUDE += \
    -I$(VPP_INCLUDE) \


