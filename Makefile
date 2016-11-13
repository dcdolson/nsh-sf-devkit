TOP := .

# examples depends on src being compiled first.
all:
	$(MAKE) -C src
	$(MAKE) -C examples

clean::
	$(MAKE) -C src clean
	$(MAKE) -C examples clean

include $(TOP)/make/macros.mk

