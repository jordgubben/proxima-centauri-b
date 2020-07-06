#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define IN_PLAY_S
#include "overview.h"

void render_player(const player_t*);

void  render_play(play_t* play) {
	// Render world
	Vector3 origo = {0,0,0};
	BeginMode3D(play->main_camera);
	{
		// Player
		render_player(&play->player);

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

	const vec3_t p = play->player.position;
	const vec3_t f = forward_from_y_rot(play->player.rotation);
	const float r = play->player.rotation;
	snprintf(str, 1024, "Player"
				"\n\tposition: [%1.2f,%1.2f,%1.2f]"
				"\n\tforward: [%1.2f,%1.2f,%1.2f]"
				"\n\trotation: [%1.2f] rad",
		p.x, p.y, p.z,
		f.x, f.y, f.z,
		r
		);
	DrawText(str, 250, 350, 15, GOLD);
}

void render_player(const player_t* player) {
	// Update model transform
	// (Note: Matrix is transposed because OpenGL is column major)
	const float r = player->rotation;
	Model model = player->model;
	model.transform =
		(Matrix)
		{ cosf(r), 0,sinf(-r), 0
		,       0, 1,       0, 0
		,sinf(+r), 0, cosf(r), 0
		,       0, 0,       0, 1
		};
	DrawModel(model, vec3_to_rl(player->position), 1, GOLD);

	// Debug
	const vec3_t p1 = player->position;
	const vec3_t f = forward_from_y_rot(player->rotation);
	vec3_t p2 = {p1.x + f.x * 2, p1.y + f.y * 2, p1.z + f.z * 2};
	DrawLine3D(vec3_to_rl(p1), vec3_to_rl(p2), MAROON);
}

