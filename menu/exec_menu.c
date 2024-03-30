#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define IN_MENU_S
#include "menu.h"
#include "play.h"

int main(int argc, char** argv) {
	printf("Hello, Proxima menu!\n");

	// Get things going
	InitWindow(640, 480, "Hello, Raylib!");
	SetTargetFPS(60);
	menu_t* menu = init_menu();

	// Alternate states
	play_t* play = NULL;
	
	// Ah-Gogogoggogogogo!
	menu_wants_t what_menu_wants = menu_wants_to_keep_going;
	while(!WindowShouldClose() && what_menu_wants != menu_wants_to_quit) {
		// Update
		if(play) {
			process_play_input(play);
			update_play(GetFrameTime(), play);
		} else {
			process_input(menu);
		}

		// Render
		BeginDrawing();
		ClearBackground(BLACK);
		if (play) {
			render_play(play);
		} else {
			what_menu_wants = present_menu(menu);
		}
		DrawFPS(0,0);
		EndDrawing();

		if(what_menu_wants == menu_wants_to_play && !play) {
			play = init_play();
		}
	}

	// Nap time
	free_play(play);
	free_menu(menu);
	CloseWindow();
	return 0;
}
