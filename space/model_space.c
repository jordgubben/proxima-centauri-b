#include <stdlib.h>
#include <stdio.h>

#define IN_PLAY_S
#include "space.h"

space_t* init_space() {
	space_t* space =  calloc(1, sizeof(space_t));

	return space;
}

void free_space(space_t* space) {
	if(!space) { return; }
	free(space);
}
