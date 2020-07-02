#include <catch2/catch.hpp>

#define IN_PLAY_S
#include "overview.h"

const float tau = 6.283185;

inline vec3_t vec3_round(vec3_t v) {
	return (vec3_t) { roundf(v.x), roundf(v.y), roundf(v.z)};
}

inline std::ostream& operator<<(std::ostream& out, const vec3_t& val) {
	out << "(" << val.x << ", " << val.y << ", " << val.z << ")";
	return out;
}

inline bool operator==(const vec3_t& lhs, const vec3_t& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

inline bool operator!=(const vec3_t& lhs, const vec3_t& rhs) { return !(lhs == rhs); }

SCENARIO("Proxima Centauri b - 'Play' subsystem"){
	play_t* play = init_play();

       // TODO: Test adding things (and verify partitioning)

	free_play(play);
}

SCENARIO("Player orientation") {
	player_t player = {0};

	GIVEN("A player that is *not* rotated") {
		REQUIRE(player.rotation == 0);

		THEN("Forward is in along the +z axis") {
			vec3_t expected = {0,0,+1};
			vec3_t actual = vec3_round(forward_from_y_rot(player.rotation));
			CHECK( actual == expected);
		}
	}

	GIVEN("A player that is rotated 90 degrees") {
		player.rotation = 0.25 * tau;

		THEN("Forward is in along the +x axis") {
			vec3_t expected = {+1,0,0};
			vec3_t actual = vec3_round(forward_from_y_rot(player.rotation));
			CHECK( actual == expected);
		}
	}

	GIVEN("A player that is rotated 180 degrees") {
		player.rotation = 0.5 * tau;

		THEN("Forward is in along the -z axis") {
			vec3_t expected = {0,0,-1};
			vec3_t actual = vec3_round(forward_from_y_rot(player.rotation));
			CHECK( actual == expected);
		}
	}

	GIVEN("A player that is rotated 270 degrees") {
		player.rotation = 0.75 * tau;

		THEN("Forward is in along the -x axis") {
			vec3_t expected = {-1,0,0};
			vec3_t actual = vec3_round(forward_from_y_rot(player.rotation));
			CHECK( actual == expected);
		}
	}
}
