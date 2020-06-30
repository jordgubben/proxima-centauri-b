#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define IN_PLAY_S
#include "overview.h"

void  render_play(play_t* play) {
	// Render world
	Vector3 origo = {0,0,0};
	BeginMode3D(play->main_camera);
	{
		// Player
		DrawModel(play->player_model, play->player_position, 1, GOLD);

		DrawGrid(10, 1.f);
		DrawGizmo(origo);
	}
	EndMode3D();

	// Render debug
	char str[1024];
	snprintf(str, 1024, "Camera\n\tposition: [%1.2f,%1.2f,%1.2f]\n\ttarget: [%1.2f,%1.2f,%1.2f]",
		play->main_camera.position.x, play->main_camera.position.y, play->main_camera.position.z,
		play->main_camera.target.x, play->main_camera.target.y, play->main_camera.target.z
		);
	DrawText(str, 50, 350, 15, DARKGREEN);
	snprintf(str, 1024, "Player"
				"\n\tposition: [%1.2f,%1.2f,%1.2f]"
				"\n\trotation: [%1.2f] rad",
		play->player_position.x, play->player_position.y, play->player_position.z,
		play->player_rotation
		);
	DrawText(str, 250, 350, 15, GOLD);
}

