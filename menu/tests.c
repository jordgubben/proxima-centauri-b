#include <stdlib.h>

#define IN_MENU_S
#include "menu.h"

void test_submodule() {
	menu_t* menu = init_menu();

	// TODO: Test adding things (and verify partitioning)

	free_menu(menu);
}

int main(int argc, char** argv ) {
	test_submodule();
	return EXIT_SUCCESS;
}

