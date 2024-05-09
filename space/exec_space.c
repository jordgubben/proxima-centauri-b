#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#include "game_state_recorder.h"

#define IN_SPACE_S
#include "space.h"

void show_gsr_info( gsr_vhs_t const *gsr ) {
	// Print positions for all ships
	const float text_size = 14;
	const float row_h = 14;
	float offset_x = 32, offset_y = 32;
	for ( gsr_tick_t const *tick = &gsr->ticks[0];
		tick < &gsr->ticks[gsr->capacity]; tick++ ) {
		char buffer[1024];

		char cursor = ' ';
		if ( tick->tick_nr == gsr_last_tick( gsr )) {
			cursor = '*';
		} else if ( tick->tick_nr == gsr_next_tick( gsr) ) {
			cursor = '>';
		}
		snprintf( buffer, 1024, "%c #%u"
			, cursor
			, tick->tick_nr
			);
		DrawText( buffer, offset_x, offset_y, text_size, BLACK );

		offset_y += row_h;
	}

}

int main(int argc, char** argv) {
	// Get things up and running
	InitWindow(640, 480, "Hello, Space subsystem!");
	SetTargetFPS(60);

	// Initialize game state recorder
	size_t gsr_size = gsr_requireed_size( 16 );
	gsr_vhs_t *gsr =
		gsr_init( gsr_size, malloc( gsr_size ));

	space_t space = {};
	init_space( &space);
	create_ship_at( 220, 240, &space);
	create_ship_at( 420, 240, &space);
	
	// Ah-Gogogoggogogogo!
	while(!WindowShouldClose()) {
		gsr_record_tick( sizeof ( space_t ), &space, gsr );

		// Update
		float dt = 1.f / 60.f;
		process_space_input(&space);
		update_space(dt, &space);

		// Render
		BeginDrawing();
		ClearBackground(RAYWHITE);
		render_space(&space);
		show_gsr_info( gsr );
		DrawFPS(0,0);
		EndDrawing();
	}

	// Nap time
	gsr_term( gsr );
	free( gsr );
	CloseWindow();
	return 0;
}
