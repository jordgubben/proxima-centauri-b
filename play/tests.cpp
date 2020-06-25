#include <catch2/catch.hpp>

#define IN_PLAY_S
#include "overview.h"

SCENARIO("Proxima Centauri b - 'Play' submodule"){
	play_t* play = init_play();

	// TODO: Test adding things (and verify partitioning)

	free_play(play);
}
