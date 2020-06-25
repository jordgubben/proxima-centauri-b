#include <stdlib.h>
#include <stdio.h>

#define IN_PLAY_S
#include "overview.h"

play_t* init_play() {
	play_t* play =  malloc(sizeof(play_t));
	return play;
}

void free_play(play_t* play) {
	free(play);
}
