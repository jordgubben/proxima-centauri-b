#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define IN_PLAY_S
#include "overview.h"

Camera3D get_main_camera(camera_mode_t, const player_t*);
void render_player(const player_t*);
void draw_rl_matrix_as_text(const char* title, Matrix m, float x, float y, float s, Color c);

void  render_play(play_t* play) {
	// Render world
	Vector3 origo = {0,0,0};

	Camera3D main_camera = get_main_camera(play->camera_mode, &play->player);
	BeginMode3D(main_camera);
	{
		// Player
		render_player(&play->player);

		DrawGrid(10, 1.f);
		DrawGizmo(origo);
	}
	EndMode3D();
	draw_rl_matrix_as_text("Camera matrix", GetCameraMatrix(main_camera), 450, 25, 10, RED);

	// Render debug
	char str[1024];
	snprintf(str, 1024, "Camera\n\tposition: [%1.2f,%1.2f,%1.2f]\n\ttarget: [%1.2f,%1.2f,%1.2f]",
		main_camera.position.x, main_camera.position.y, main_camera.position.z,
		main_camera.target.x, main_camera.target.y, main_camera.target.z
		);
	DrawText(str, 50, 350, 15, DARKGREEN);

	const vec3_t p = play->player.position;
	const vec3_t v = play->player.velocity;
	const vec3_t f = forward_from_y_rot(play->player.rotation);
	const float r = play->player.rotation;
	snprintf(str, 1024, "Player"
				"\n\tposition: [%1.2f,%1.2f,%1.2f]"
				"\n\tvelocity: [%1.2f,%1.2f,%1.2f] (%2.02f m/s | %2.02f km/h)"
				"\n\tforward: [%1.2f,%1.2f,%1.2f]"
				"\n\trotation: [%1.2f] rad",
		p.x, p.y, p.z,
		v.x, v.y, v.z, vec3_length(v), 3.6f * vec3_length(v),
		f.x, f.y, f.z,
		r
		);
	DrawText(str, 250, 350, 15, GOLD);
}

Camera3D get_main_camera(camera_mode_t camera_mode, const player_t* player) {
	const vec3_t up = {0,1,0};
	const vec3_t above_player = vec3_add(player->position, up);

	// Setup camera defaults
	Camera3D main_camera = {0};
	main_camera.position = (Vector3) {0,5,0};
	main_camera.target = (Vector3) {0, 0, 1};
	main_camera.up = (Vector3) {0,1,0};
	main_camera.fovy = 45.f;

	switch(camera_mode) {
		case cm_static_fixed:
			main_camera.position = (Vector3) {0,5,10};
			main_camera.target = (Vector3) { 0, 1, 0};
			break;

		case cm_static_follow:
			main_camera.position = (Vector3) {0,5,0};
			main_camera.target = vec3_to_rl(player->position);
			break;

		case cm_on_the_nose:
			main_camera.position =
				vec3_to_rl(above_player);
			main_camera.target =
				vec3_to_rl(vec3_add(above_player, forward_from_y_rot(player->rotation)));
			break;

		// Not a mode - Silence compilation warning
		case  num_camera_modes:  break;
	}

	return main_camera;
}

void draw_rl_matrix_as_text(const char* title, Matrix m, float x, float y, float s, Color c) {
	char str[1024];
	snprintf(str, 1024, "%s:\n"
		"[ %1.2f, %1.2f, %1.2f, %1.2f|\n"
		"| %1.2f, %1.2f, %1.2f, %1.2f|\n"
		"| %1.2f, %1.2f, %1.2f, %1.2f|\n"
		"| %1.2f, %1.2f, %1.2f, %1.2f]",
		title,
		m.m0, m.m4, m.m8, m.m12,
		m.m1, m.m5, m.m9, m.m13,
		m.m2, m.m6, m.m10, m.m14,
		m.m3, m.m7, m.m11, m.m15
		);
	DrawText(str, x, y, s, c);
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

