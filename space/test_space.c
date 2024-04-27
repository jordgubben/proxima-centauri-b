#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define IN_SPACE_S
#include "space.h"

void test_space_submodule() {
	InitWindow(200, 100, "Play subsystem windowed test");
	space_t space = {};
	init_space( &space);

	// TODO: Preform windowed tests

	CloseWindow();
}


int main(int argc, const char** argv)
{
	printf("Testing 'space' subsystem.\n");
	return EXIT_SUCCESS;
}
