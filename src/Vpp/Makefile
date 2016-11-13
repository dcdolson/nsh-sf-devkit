TOP := ../..

LIB:=$(TOP)/lib/libvpp.a

all:: $(LIB)

OBJS := $(addprefix obj/, \
    VppNetInterface.o \
    VppIntegration.o \
    )

include $(TOP)/make/macros.mk

ifeq ($(VPP_INCLUDE),)
$(error "Please define VPP_INCLUDE environment variable")
endif

LOCAL_INCLUDE += \
    -I$(VPP_INCLUDE) \


