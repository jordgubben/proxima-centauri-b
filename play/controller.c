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
}

void update_player_physics(float, player_t*);

void update_play(float dt, play_t* play) {
	update_player_physics(dt, &play->player);
}

void update_player_physics(float dt, player_t* player) {
	// Rotate player
	player->rotation += player->rotation_dir * dt * tau;
	player->rotation -= floorf(player->rotation/tau) * tau;

	// Update model transform
	// (Note: Matrix is transposed because OpenGL is column major)
	const float r = player->rotation;
	player->model.transform =
		(Matrix)
		{ cosf(r), 0,sinf(-r), 0
		,       0, 1,       0, 0
		,sinf(+r), 0, cosf(r), 0
		,       0, 0,       0, 1
		};
}
