TOP := .

# examples depends on src being compiled first.
all:
	$(MAKE) -C src
	$(MAKE) -C examples

include $(TOP)/make/macros.mk

