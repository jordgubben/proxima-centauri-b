#include <assert.h>
#include <stdlib.h>
#include <raylib.h>

#define IN_SPACE_S
#include "space.h"

void test_space_submodule() {
	InitWindow(200, 100, "Play subsystem windowed test");
	space_t* space = init_space();

	// TODO: Preform windowed tests

	free_space(space);
	CloseWindow();
}

int main(int argc, const char** argv)
{
	return EXIT_SUCCESS;
}
