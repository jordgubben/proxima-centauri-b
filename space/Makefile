# Build 'space' subsystem
SUBSYSTEM=space
CFLAGS=-std=c11 -g -I include/ $(shell pkg-config --cflags raylib)
LDFLAGS=$(shell pkg-config --libs raylib)

.PHONY: clean run check all

all: run-$(SUBSYSTEM) run-tests

run: run-$(SUBSYSTEM)
	./run-$(SUBSYSTEM)

check: run-tests
	./run-tests

run-$(SUBSYSTEM): exec_$(SUBSYSTEM).c include/$(SUBSYSTEM).h implement_$(SUBSYSTEM).c
	$(CC) $(CFLAGS) $(LDFLAGS) $< implement_$(SUBSYSTEM).c -o $@

run-tests: test_$(SUBSYSTEM).c include/$(SUBSYSTEM).h implement_$(SUBSYSTEM).c
	$(CC) $(CFLAGS) $(LDFLAGS) $< implement_$(SUBSYSTEM).c -o $@

clean:
	rm -rvf run-*
