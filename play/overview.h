#ifndef PLAY_OVERVIEW_H
#define PLAY_OVERVIEW_H
#else
#warning "Header file included more than once."
#endif

// Includes //
#ifdef IN_PLAY_S
#include <raylib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Types //
typedef union vec3_t {
	struct { float x, y, z; };
	struct { float r, g, b; };
	float arr[3];
} vec3_t;

typedef struct player_ player_t;
#ifdef IN_PLAY_S
typedef struct player_ {
	bool go_forward;
	vec3_t position, velocity;
	float rotation, rotation_dir;
	Model model;
} player_t;
#endif

typedef struct play_ play_t;
#ifdef IN_PLAY_S
typedef struct play_ {
	Camera3D main_camera;
	player_t player;
} play_t;
#endif

// Model //
play_t* init_play();
void free_play(play_t*);

// View //
void render_play(play_t*);

// Controller //
void process_play_input(play_t*);
void update_play(float, play_t*);
vec3_t forward_from_y_rot(float);

// Linalg //
#ifdef IN_PLAY_S
static inline Vector3 vec3_to_rl(vec3_t v) { return (Vector3) { v.x, v.y, v.z};}
#endif

#ifdef __cplusplus
} // extern "C"
#endif
