# Makefile that calls the other make file
# (This must be updated every time a subsystem is added)

.PHONY: all clean

all:
	cd play && $(MAKE) all
	cd menu && $(MAKE) all

check:
	cd play && $(MAKE) check
	cd menu && $(MAKE) check

clean:
	cd play && $(MAKE) clean
	cd menu && $(MAKE) clean
