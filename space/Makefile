CFLAGS=-std=c11 -g -I include/ $(shell pkg-config --cflags raylib)
LDFLAGS=$(shell pkg-config --libs raylib)

# Define subsystem core
CORE_SOURCES=$(patsubst %.c,_%.o, $(subst test_space.c,,$(subst exec_space.c,,$(wildcard *.c))))
CORE_OBJECTS= $(patsubst %.c,_%.o, $(CORE_SOURCES))

.PHONY: clean run check all

all: run-space run-tests

run: run-space
	./run-space

check: run-tests
	./run-tests

run-space: exec_space.c include/space.h libspace.a
	$(CC) $(CFLAGS) $(LDFLAGS) $< libspace.a -o $@

run-tests: test_space.c include/space.h libspace.a
	$(CC) $(CFLAGS) $(LDFLAGS) $< libspace.a -o $@

# Bundle core object files
libspace.a: $(CORE_OBJECTS) include/space.h
	$(AR) rcs $@ $(CORE_OBJECTS)

# Build all object files
_%.o: %.c include/space.h
	$(CC) -c  $(CFLAGS) $< -o $@

clean:
	rm -rvf run-*
	rm -vf *.o
	rm -vf *.a
