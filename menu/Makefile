CFLAGS=-std=c11 -g -I include/ -I ../play/include/

# Object files for the corresponding C source files
# Excluding app_root.c and tests.c since they have main functions.
OBJS= $(patsubst %.c,_%.o,$(subst tests.c,,$(subst app_root.c,,$(wildcard *.c))))

# Link time dependencies
DEPS= ../play/libplay.a

.PHONY: clean run check all

all: run-menu run-tests

run: run-menu
	./run-menu

check: run-tests
	./run-tests

# Build main executable
run-menu: app_root.c include/menu.h $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) $(DEPS) -lraylib -o $@

# Build test executable
run-tests: tests.c include/menu.h $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -lraylib -o $@

# Build all object files
_%.o: %.c include/menu.h
	$(CC) -c  $(CFLAGS) $< -o $@

clean:
	rm -rvf run-*
	rm -vf *.o
	rm -vf *.a
