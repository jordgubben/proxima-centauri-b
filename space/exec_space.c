#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define IN_SPACE_S
#include "space.h"

int main(int argc, char** argv) {
	// Get things up and running
	InitWindow(640, 480, "Hello, Space subsystem!");
	SetTargetFPS(60);
	space_t space = {};
	init_space( &space);
	create_ship_at( 220, 240, &space);
	create_ship_at( 420, 240, &space);
	
	// Ah-Gogogoggogogogo!
	while(!WindowShouldClose()) {
		// Update
		float dt = 1.f / 60.f;
		process_space_input(&space);
		update_space(dt, &space);

		// Render
		BeginDrawing();
		ClearBackground(RAYWHITE);
		render_space(&space);
		DrawFPS(0,0);
		EndDrawing();
	}

	// Nap time
	CloseWindow();
	return 0;
}
