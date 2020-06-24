#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

#define IN_MENU_S
#include "overview.h"

typedef struct {
	float offset_x, offset_y;
	int item_index;
} item_placement_t;

bool present_item(menu_t*, item_placement_t*, const char*);

menu_wants_t present_menu(menu_t* menu) {
	menu_wants_t want = menu_wants_to_keep_going;

	BeginDrawing();
	ClearBackground(BLACK);

	item_placement_t placement = {100.f, 300.f, 0};
	float font_size = 20;
	float margin_y = 10;

	if(present_item(menu, &placement, "Start game")) {
		printf("Selected: 'Start game'\n");
	}

	if(present_item(menu, &placement, "Credits")) {
		printf("Selected: 'Credits'\n");
	}

	if(present_item(menu, &placement, "Quit")) {
		printf("Selected: 'Quit'\n");
		want = menu_wants_to_quit;
	}

	// Return to the top when reaching the bottom
	menu->current_index %= placement.item_index;

	DrawFPS(0,0);
	EndDrawing();

	return want;
}

bool present_item(menu_t* menu, item_placement_t* placement, const char* label) {
	const float font_size = 20;
	const float margin_y = 10;

	bool current = menu->current_index == placement->item_index++;
	Color color = current ? LIGHTGRAY : DARKGRAY;
	DrawText(label, placement->offset_x, placement->offset_y, font_size, color);
	placement->offset_y += margin_y + font_size;
	return current && menu->current_selected;
}
