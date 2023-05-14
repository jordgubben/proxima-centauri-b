# Makefile that calls the other make file
# (This must be updated every time a subsystem is added)

.PHONY: all clean

all:
	cd play && $(MAKE) all
	cd menu && $(MAKE) all

apps:
	cd play && $(MAKE) run-play
	cd menu && $(MAKE) run-menu

check:
	cd play && $(MAKE) check
	cd menu && $(MAKE) check

clean:
	cd play && $(MAKE) clean
	cd menu && $(MAKE) clean
