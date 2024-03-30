CFLAGS=-std=c11 -g -I include/ -I ../play/include/

# Define subsystem core
CORE_SOURCES=$(patsubst %.c,_%.o, $(subst test_menu.c,,$(subst exec_menu.c,,$(wildcard *.c))))
CORE_OBJECTS= $(patsubst %.c,_%.o, $(CORE_SOURCES))

# Link time dependencies
DEPS= ../play/libplay.a

.PHONY: clean run check all

all: run-menu run-tests

run: run-menu
	./run-menu

check: run-tests
	./run-tests

# Build main executable
run-menu: exec_menu.c include/menu.h libmenu.a
	$(CC) $(CFLAGS) $< libmenu.a $(DEPS) -lraylib -o $@

# Build test executable
run-tests: test_menu.c include/menu.h libmenu.a
	$(CC) $(CFLAGS) $< libmenu.a -lraylib -o $@

# Bundle core object files
libmenu.a: $(CORE_OBJECTS) include/menu.h
	$(AR) rcs $@ $(CORE_OBJECTS)

# Build all object files
_%.o: %.c include/menu.h
	$(CC) -c  $(CFLAGS) $< -o $@

clean:
	rm -rvf run-*
	rm -vf *.o
	rm -vf *.a
