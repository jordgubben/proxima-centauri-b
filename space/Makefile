# Build 'space' subsystem
SUBSYSTEM=space

# Compiler flags
CFLAGS=-std=c11
CFLAGS+=-g
CFLAGS+=-I include/
CFLAGS+=$(shell pkg-config --cflags raylib)

# Linker flags
LDFLAGS=$(shell pkg-config --libs raylib)

# Targets that are not files
.PHONY: clean run check all

all: run-$(SUBSYSTEM) run-tests

run: run-$(SUBSYSTEM)
	./run-$(SUBSYSTEM)

check: run-tests
	./run-tests

run-$(SUBSYSTEM): exec_$(SUBSYSTEM).c include/$(SUBSYSTEM).h implement_$(SUBSYSTEM).c *.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< implement_$(SUBSYSTEM).c -o $@

run-tests: test_$(SUBSYSTEM).c include/$(SUBSYSTEM).h implement_$(SUBSYSTEM).c *.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< implement_$(SUBSYSTEM).c -o $@

clean:
	rm -rvf run-*
