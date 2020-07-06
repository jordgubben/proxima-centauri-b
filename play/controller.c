#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <raylib.h>

#define IN_PLAY_S
#include "overview.h"

const float tau = 6.28;

void process_play_input(play_t* play) {
	if(IsKeyDown(KEY_LEFT)) {
		play->player.rotation_dir = -1;
	} else if (IsKeyDown(KEY_RIGHT)) {
		play->player.rotation_dir = +1;
	} else {
		play->player.rotation_dir = 0;
	}

	play->player.go_forward = IsKeyDown(KEY_UP);
}

void update_player_physics(float, player_t*);

void update_play(float dt, play_t* play) {
	update_player_physics(dt, &play->player);
}


vec3_t vec3_add(vec3_t, vec3_t);
vec3_t vec3_scaled_by(float, vec3_t);

void update_player_physics(float dt, player_t* player) {
	// Accelerate player
	vec3_t acceleration = {0};
	if (player->go_forward) {
		vec3_t forward = forward_from_y_rot(player->rotation);
		acceleration = vec3_scaled_by(10, forward);
	}
	const linear_friction = 2;
	acceleration = vec3_add(acceleration, vec3_scaled_by(-linear_friction, player->velocity));
	player->position = vec3_add(player->position, vec3_scaled_by(dt, player->velocity));
	player->position = vec3_add(player->position, vec3_scaled_by(dt*dt/2.f, acceleration));
	player->velocity = vec3_add(player->velocity, vec3_scaled_by(dt, acceleration));

	// Rotate player
	player->rotation += player->rotation_dir * dt * tau;
	player->rotation -= floorf(player->rotation/tau) * tau;
}

vec3_t vec3_add(vec3_t v1, vec3_t v2) {
	return (vec3_t) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

vec3_t vec3_scaled_by(float s, vec3_t v) {
	return (vec3_t) { v.x * s, v.y * s, v.z * s };
}

vec3_t forward_from_y_rot(float y_rad) {
	return (vec3_t) {-sinf(y_rad), 0, cosf(y_rad)};
}
