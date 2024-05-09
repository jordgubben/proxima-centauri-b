#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IN_SPACE_S
#include "space.h"

#include "game_state_recorder.h"

const float tau = 6.28;
const float ship_acceleration = 500;
const float ship_deceleration = 600;
const float ship_max_speed = 250;
const float ship_min_speed = 50;

////////////////////////////////////////////////////////////////////////////////
// Model 'space' subsystem

void init_space(space_t* space) {
	assert( space );
}

uint16_t create_ship_at( float x, float y, space_t *space) {
	assert( space );
	assert( space->num_ships <  max_ships );

	// Create a new ship at the given position
	ship_t *new_ship = &space->ships[space->num_ships];
	new_ship->px = x;
	new_ship->py = y;
	new_ship->vx = 0;
	new_ship->vy = 0;

	return space->num_ships++;
}


////////////////////////////////////////////////////////////////////////////////
// Update 'space' subsystem

void process_space_input(space_t* space) {
	assert( space );
	if ( space->num_ships == 0 ) return;

	// Steer the player ship (always at index 0)
	ship_t *player_ship = &space->ships[0];
	player_ship->dx = 0; player_ship->dy = 0;
	if ( IsKeyDown( KEY_LEFT ) ) { player_ship->dx = -1; }
	if ( IsKeyDown( KEY_RIGHT ) ) { player_ship->dx = +1; }
	if ( IsKeyDown( KEY_UP ) ) { player_ship->dy = -1; }
	if ( IsKeyDown( KEY_DOWN ) ) { player_ship->dy = +1; }
}


void update_space(float dt, space_t* space) {
	// Move all ships
	for ( ship_t *ship = &space->ships[0];
		ship < &space->ships[space->num_ships]; ship++ ) {
		ship->px += ship->vx * dt;
		ship->py += ship->vy * dt;
	}

	// Accelerate all ships (up to max speed)
	for ( ship_t *ship = &space->ships[0];
		ship < &space->ships[space->num_ships]; ship++ ) {

		// Accelerate if *horizontal* key is pressed, and decelerate otherwise.
		if ( fabs( ship->dx ) > 0.1 ) {
			ship->vx += ship->dx * dt * ship_acceleration;
		} else if ( fabs( ship->vx ) > 0 ) {
			float dir_x = (ship->vx / fabs(ship->vx));
			ship->vx -= dir_x * dt * ship_deceleration;
		}

		// Accelerate if *vertically* key is pressed, and decelerate otherwise.
		if ( fabs( ship->dy ) > 0.1 ) {
			ship->vy += ship->dy * dt * ship_acceleration;
		} else if ( fabs( ship->vy ) > 0 ) {
			float dir_y = (ship->vy / fabs(ship->vy));
			ship->vy -= dir_y * dt * ship_deceleration;
		}

		// Slow down if over max speed.
		float speed = sqrt( ship->vx * ship->vx + ship->vy * ship->vy );
		if ( speed > ship_max_speed ) {
			ship->vx *= ship_max_speed/speed;
			ship->vy *= ship_max_speed/speed;
		}

		// Prevent shaking in place
		bool steering = fabs( ship->dx ) > 0 || fabs( ship->dy ) > 0;
		if ( speed < ship_min_speed && !steering ) {
			ship->vx = 0;
			ship->vy = 0;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// Render 'space' subsystem

void  render_space(space_t const* space) {

	// Draw all ships
	for ( ship_t const *ship = &space->ships[0];
		ship < &space->ships[space->num_ships]; ship++ ) {
		Vector2 pos = { ship->px, ship->py };
		DrawCircleV(pos, 25, DARKBLUE);
	}

	// Print positions for all ships
	const float row_h = 40;
	float offset_x = 32, offset_y = 480 - space->num_ships * row_h;
	for ( ship_t const *ship = &space->ships[0];
		ship < &space->ships[space->num_ships]; ship++ ) {
		char buffer[1024];

		snprintf( buffer, 1024, "(%.01f,%.01f)"
			, ship->px, ship->py
			);
		DrawText( buffer, offset_x, offset_y, 32, DARKGRAY );

		snprintf( buffer, 1024, "[%.02f,%.02f]"
			, ship->vx, ship->vy
			);
		DrawText( buffer, offset_x + 224, offset_y, 32, DARKGRAY );

		offset_y += row_h;
	}
}

#define IMPLEMENT_ME_SENPAI
#include "game_state_recorder.h"
