#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define IN_MENU_S
#include "overview.h"

int main(int argc, char** argv) {
	printf("Hello, Proxima menu!\n");

	// Get things going
	InitWindow(640, 480, "Hello, Raylib!");
	SetTargetFPS(60);
	menu_t* menu = init_menu();
	
	// Ah-Gogogoggogogogo!
	while(!WindowShouldClose()) {
		process_input(menu);
		present_menu(menu);
	}

	// Nap time
	free_menu(menu);
	CloseWindow();
	return 0;
}
