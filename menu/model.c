#include <stdlib.h>
#include <stdio.h>

#define IN_MENU_S
#include "overview.h"

menu_t* init_menu() {
	menu_t* menu =  malloc(sizeof(menu_t));
	menu->state = main_menu_state;
	menu->current_item_index = 0;
	menu->current_item_selected = false;
	return menu;
}

void free_menu(menu_t* menu) {
	free(menu);
}
