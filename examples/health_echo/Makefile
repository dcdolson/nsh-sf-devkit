TOP := ../..

OBJS := $(addprefix obj/, \
    health_echo.o \
    HealthEcho.o \
    )

LIBS :=  Interfaces 

STDLIBS := stdc++

all: obj/health_echo

obj/health_echo: $(OBJS) $(addsuffix .a,$(addprefix $(TOP)/lib/lib,$(LIBS)))
	$(CC) -o $@ $(OBJS) -L$(TOP)/lib $(addprefix -l,$(LIBS) $(STDLIBS))


include ../../make/macros.mk

