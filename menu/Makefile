CFLAGS=-std=c11
CXXFLAGS=-std=c++17
OBJS= _model.o \
	_view.o \
	_controller.o \


.PHONY: clean run check all

all: run-menu run-tests

run: run-menu
	./run-menu

check: run-tests
	./run-tests

run-menu: app.c overview.h $(OBJS)
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
	rm -vf run-*
	rm -vf *.o
	rm -vf *.a
