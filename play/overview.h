#ifndef PLAY_OVERVIEW_H
#define PLAY_OVERVIEW_H
#else
#warning "Header file included more than once."
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Types //
typedef struct play_ play_t;
#ifdef IN_PLAY_S
typedef struct play_ {

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


#ifdef __cplusplus
} // extern "C"
#endif
