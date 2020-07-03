CFLAGS=-std=c11 -g
CXXFLAGS=-std=c++17 -g

# Define subsystem core
CORE_SOURCES= $(subst app_root.c,,$(wildcard *.c))
CORE_OBJECTS= $(patsubst %.c,_%.o, $(CORE_SOURCES))

.PHONY: clean run check all

all: run-play run-tests

run: run-play
	./run-play

check: run-tests
	./run-tests

check-windowed: run-tests
	./run-tests "[windowed]"

run-play: app_root.c overview.h libplay.a
	$(CC) $(CFLAGS) $< libplay.a  -lraylib -o $@

run-tests: tests.cpp overview.h libplay.a libcatch2.a
	$(CXX) $(CXXFLAGS) $< libplay.a libcatch2.a -lraylib -o $@

# Bundle core object files
libplay.a: $(CORE_OBJECTS) overview.h
	$(AR) rcs $@ $(CORE_OBJECTS)

# Build all object files
_%.o: %.c overview.h
	$(CC) -c  $(CFLAGS) $< -o $@

# Avoid building catch2 implementation so often
# https://github.com/catchorg/Catch2/blob/master/docs/slow-compiles.md
libcatch2.a: catch2_lib.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rvf run-*
	rm -vf *.o
	rm -vf *.a
