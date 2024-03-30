CFLAGS=-std=c11 -g -I include/

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

run-play: app_root.c include/play.h libplay.a
	$(CC) $(CFLAGS) $< libplay.a -lraylib -o $@

run-tests: tests.c include/play.h libplay.a
	$(CC) $(CFLAGS) $< libplay.a -lraylib -o $@

# Bundle core object files
libplay.a: $(CORE_OBJECTS) include/play.h
	$(AR) rcs $@ $(CORE_OBJECTS)

# Build all object files
_%.o: %.c include/play.h
	$(CC) -c  $(CFLAGS) $< -o $@

clean:
	rm -rvf run-*
	rm -vf *.o
	rm -vf *.a
