#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <raylib.h>

#define IN_PLAY_S
#include "overview.h"

const float tau = 6.28;

void process_play_input(play_t* play) {
	if(IsKeyDown(KEY_LEFT)) {
		play->player_rotation_dir = -1;
	} else if (IsKeyDown(KEY_RIGHT)) {
		play->player_rotation_dir = +1;
	} else {
		play->player_rotation_dir = 0;
	}
}

void update_play(float dt, play_t* play) {
	// Rotate player clockwise (as seen from above)
	// (Note: Matrix is transposed because OpenGL is column major)
	play->player_rotation += play->player_rotation_dir * dt * tau;
	play->player_rotation -= floorf(play->player_rotation/tau) * tau;
	const float r = play->player_rotation;
	play->player_model.transform =
		(Matrix)
		{ cosf(r), 0,sinf(-r), 0
		,       0, 1,       0, 0
		,sinf(+r), 0, cosf(r), 0
		,       0, 0,       0, 1
		};
}
