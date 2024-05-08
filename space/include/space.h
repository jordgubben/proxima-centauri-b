#ifndef SPACE_OVERVIEW_H
#define SPACE_OVERVIEW_H
#else
#warning "Header file included more than once."
#endif

// Includes //
#ifdef IN_SPACE_S
#include <math.h>
#include <raylib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ship_ {
	float px, py;
	float dx, dy;
	float vx, vy;
} ship_t;

enum space_e {
	max_ships = 16,
};

typedef struct space_ {
	// All ship
	uint16_t num_ships;
	ship_t ships[max_ships];
} space_t;

// Model //
void init_space(space_t*);
uint16_t create_ship_at( float x, float y, space_t*);

// View //
void render_space(space_t const*);

// Controller //
void process_space_input(space_t*);
void update_space(float, space_t*);


#ifdef __cplusplus
} // extern "C"
#endif
