#include <stdlib.h>
#include <stdio.h>

#define IN_PLAY_S
#include "overview.h"

play_t* init_play() {
	play_t* play =  calloc(1, sizeof(play_t));

	// Init camera
	play->camera_mode = cm_static_fixed;
	play->main_camera.position = (Vector3) {1,5,10};
	play->main_camera.target = (Vector3) {0, 0, 0};
	play->main_camera.up = (Vector3) {0,1,0};
	play->main_camera.fovy = 45.f;

	// Init player
	play->player.position = (vec3_t) {0, 0.5f, 0};
	play->player.model =  LoadModelFromMesh(GenMeshCube(2,1,2));

	return play;
}

void free_play(play_t* play) {
	if(!play) { return; }
	UnloadModel(play->player.model);
	free(play);
}
