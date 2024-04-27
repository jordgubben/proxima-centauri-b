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

typedef struct space_ {
} space_t;

// Model //
void init_space(space_t*);

// View //
void render_space(space_t const*);

// Controller //
void process_space_input(space_t*);
void update_space(float, space_t*);


#ifdef __cplusplus
} // extern "C"
#endif
