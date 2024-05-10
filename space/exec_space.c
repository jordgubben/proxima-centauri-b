#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#include "game_state_recorder.h"

#define IN_SPACE_S
#include "space.h"

void show_gsr_info( gsr_vhs_t const *gsr ) {
	const uint32_t segment_size = 48;
	uint32_t first_tick = segment_size * ( gsr_next_tick( gsr ) / segment_size );
	uint32_t last_tick = first_tick + segment_size;

	// Print positions for all ships
	const float text_size = 8;
	const float row_h = 8;
	float offset_x = 16, offset_y = 24;
	for ( int tick_nr = first_tick; tick_nr < last_tick; tick_nr++ ) {
		char buffer[1024];
		char cursor = ' ';
		if ( tick_nr == gsr_last_tick( gsr )) {
			cursor = '<';
		} else if ( tick_nr == gsr_next_tick( gsr) ) {
			cursor = '>';
		}
		char data = gsr_has_tick( tick_nr, gsr) ? 'O' : 'X';
		Color color = gsr_has_tick( tick_nr, gsr) ? BLACK : LIGHTGRAY;
		snprintf( buffer, 1024, "|%c| %c #%u"
			, data
			, cursor
			, tick_nr
			);
		DrawText( buffer, offset_x, offset_y, text_size, color );

		offset_y += row_h;
	}

}

int main(int argc, char** argv) {
	// Get things up and running
	InitWindow(640, 480, "Hello, Space subsystem!");
	SetTargetFPS(60);
	bool paused = false;

	// Initialize game state recorder
	// (1024 ticks ≈ 17 seconds)
	size_t gsr_size = gsr_requireed_size( 1024 );
	gsr_vhs_t *gsr =
		gsr_init( gsr_size, malloc( gsr_size ));

	space_t space = {};
	init_space( &space);
	create_ship_at( 220, 240, &space);
	create_ship_at( 420, 240, &space);
	
	// Ah-Gogogoggogogogo!
	while(!WindowShouldClose()) {
		float dt = 1.f / 60.f;

		// Playback controls
		if ( IsKeyPressed( KEY_P ) ) {
			paused = !paused;
		}
		bool rewinding = IsKeyDown( KEY_R );

		// Update (or otherwise manipulate) game state.
		if ( rewinding ) {
			gsr_step_back( gsr );
			gsr_restore_last( gsr, sizeof( space_t ), &space );
		} else if ( !paused ) {
			gsr_record_tick( sizeof ( space_t ), &space, gsr );
			process_space_input(&space);
			update_space(dt, &space);
		}

		// Render regardless of what we're doing.
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
