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
	menu_wants_t what_menu_wants = menu_wants_to_keep_going;
	while(!WindowShouldClose() && what_menu_wants != menu_wants_to_quit) {
		process_input(menu);

		// Render menu
		BeginDrawing();
		ClearBackground(BLACK);
		what_menu_wants = present_menu(menu);
		DrawFPS(0,0);
		EndDrawing();

		if(what_menu_wants == menu_wants_to_play) {
			printf("User requested to play the game, but that's not an option (yet).\n");
			what_menu_wants = menu_wants_to_keep_going;
		}
	}

	// Nap time
	free_menu(menu);
	CloseWindow();
	return 0;
}
