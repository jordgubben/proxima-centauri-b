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

	if (IsKeyPressed(KEY_C)) {
		play->camera_mode += 1;
		play->camera_mode %= num_camera_modes;
		printf("Camera mode changed to [%u]\n", play->camera_mode);
	}
}

void update_player_physics(float, player_t*);
void update_camera(play_t*);

void update_play(float dt, play_t* play) {
	update_player_physics(dt, &play->player);
	update_camera(play);
}


vec3_t vec3_add(vec3_t, vec3_t);
vec3_t vec3_scaled_by(float, vec3_t);

// Maximum velocity ≈ 20 m/s
const float forward_acceleration = 40;
const float linear_deacceleration = 2;

void update_player_physics(float dt, player_t* player) {
	// Accelerate player
	vec3_t acceleration = {0};
	if (player->go_forward) {
		vec3_t forward = forward_from_y_rot(player->rotation);
		acceleration = vec3_scaled_by(forward_acceleration, forward);
	}
	acceleration = vec3_add(acceleration, vec3_scaled_by(-linear_deacceleration, player->velocity));
	player->position = vec3_add(player->position, vec3_scaled_by(dt, player->velocity));
	player->position = vec3_add(player->position, vec3_scaled_by(dt*dt/2.f, acceleration));
	player->velocity = vec3_add(player->velocity, vec3_scaled_by(dt, acceleration));

	// Rotate player
	player->rotation += player->rotation_dir * dt * tau;
	player->rotation -= floorf(player->rotation/tau) * tau;
}

void update_camera(play_t* play) {
	const vec3_t up = {0,1,0};
	const vec3_t above_player = vec3_add(play->player.position, up);
	switch(play->camera_mode) {
		case cm_static_fixed:
			play->main_camera.position = (Vector3) {0,5,10};
			play->main_camera.target = (Vector3) { 0, 1, 0};
			break;

		case cm_static_follow:
			play->main_camera.position = (Vector3) {0,5,0};
			play->main_camera.target = vec3_to_rl(play->player.position);
			break;

		case cm_on_the_nose:
			play->main_camera.position =
				vec3_to_rl(above_player);
			play->main_camera.target =
				vec3_to_rl(vec3_add(above_player, forward_from_y_rot(play->player.rotation)));
			break;

		// Not a mode - Silence compilation warning
		case  num_camera_modes:  break;
	}
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
