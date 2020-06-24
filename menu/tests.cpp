#include <catch2/catch.hpp>

#include "overview.h"

SCENARIO("Proxima Centauri b - 'Menu' submodule"){
	menu_t* menu = init_menu();

	// TODO: Test adding things (and verify partitioning)

	free_menu(menu);
}
