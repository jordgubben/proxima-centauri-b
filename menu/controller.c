#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define IN_MENU_S
#include "overview.h"

void process_input(menu_t* menu) {
	if(IsKeyPressed(KEY_UP)) {
		menu->current_item_index--;
	}

	if(IsKeyPressed(KEY_DOWN)) {
		menu->current_item_index++;
	}

	menu->current_item_selected = IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER);
}
