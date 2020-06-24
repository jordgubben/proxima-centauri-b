#include <stdlib.h>
#include <stdio.h>

#define IN_MENU_S
#include "overview.h"

menu_t* init_menu() {
	menu_t* menu =  malloc(sizeof(menu_t));
	return menu;
}

void free_menu(menu_t* menu) {
	free(menu);
}
