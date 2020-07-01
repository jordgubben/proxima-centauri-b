CFLAGS=-std=c11 -g
CXXFLAGS=-std=c++17 -g

# Object files for the corresponding C source files
# (excuding app.c since it's not linked to the test runner)
OBJS= $(patsubst %.c,_%.o,$(subst app.c,,$(wildcard *.c)))

.PHONY: clean run check all

all: run-play run-tests

run: run-play
	./run-play

check: run-tests
	./run-tests

run-play: app.c overview.h $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -lraylib -o $@

run-tests: tests.cpp overview.h $(OBJS) libcatch2.a
	$(CXX) $(CXXFLAGS) $< $(OBJS) libcatch2.a -lraylib -o $@

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
