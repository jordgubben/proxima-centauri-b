#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define IN_PLAY_S
#include "overview.h"

int main(int argc, char** argv) {
	// Get things up and running
	InitWindow(640, 480, "Hello, Play subsystem!");
	SetTargetFPS(60);
	play_t* play = init_play();
	
	// Ah-Gogogoggogogogo!
	while(!WindowShouldClose()) {
		// Update
		float dt = 1.f / 60.f;
		process_play_input(play);
		update_play(dt, play);

		// Render
		BeginDrawing();
		ClearBackground(RAYWHITE);
		render_play(play);
		DrawFPS(0,0);
		EndDrawing();
	}

	// Nap time
	free_play(play);
	CloseWindow();
	return 0;
}
