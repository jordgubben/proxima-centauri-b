#include <assert.h>
#include <stdlib.h>

#define IN_PLAY_S
#include "play.h"

static const float tau = 6.283185;

vec3_t vec3_round(vec3_t v) {
	return (vec3_t) { roundf(v.x), roundf(v.y), roundf(v.z)};
}

bool vec3_equals(vec3_t lhs, vec3_t rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

void test_submodule() {
	InitWindow(200, 100, "Play subsystem windowed test");
	play_t* play = init_play();

	// TODO: Preform windowed tests

	free_play(play);
	CloseWindow();
}

void test_player_rotation() {
	player_t player = {0};

	// GIVEN A player that is *not* rotated
	{
		assert( player.rotation == 0.f);

		// THEN Forward is in along the +z axis
		{
			vec3_t expected = {0,0,+1};
			vec3_t actual = vec3_round(forward_from_y_rot(player.rotation));
			assert( vec3_equals(actual, expected));
		}
	}

	// GIVEN A player that is rotated 90 degrees
	{
		player.rotation = 0.25 * tau;

		// THEN Forward is in along the -x axis
		{
			vec3_t expected = {-1,0,0};
			vec3_t actual = vec3_round(forward_from_y_rot(player.rotation));
			assert( vec3_equals( actual, expected));
		}
	}

	// GIVEN A player that is rotated 180 degrees
	{
		player.rotation = 0.5 * tau;

		// THEN Forward is in along the -z axis
		{
			vec3_t expected = {0,0,-1};
			vec3_t actual = vec3_round(forward_from_y_rot(player.rotation));
			assert( vec3_equals( actual, expected));
		}
	}

	// GIVEN A player that is rotated 270 degrees
	{
		player.rotation = 0.75 * tau;

		// THEN Forward is in along the +x axis
		{
			vec3_t expected = {+1,0,0};
			vec3_t actual = vec3_round(forward_from_y_rot(player.rotation));
			assert( vec3_equals( actual, expected));
		}
	}
}


int main(int argc, const char** argv)
{
	test_player_rotation();
}
