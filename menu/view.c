#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

#define IN_MENU_S
#include "overview.h"

typedef struct {
	float offset_x, offset_y;
	int item_index;
} item_placement_t;

menu_wants_t present_main_menu(menu_t*);
void present_credits(menu_t*);
bool present_item(menu_t*, item_placement_t*, const char*);

menu_wants_t present_menu(menu_t* menu) {
	menu_wants_t want = menu_wants_to_keep_going;

	switch(menu->state) {
	case main_menu_state: want = present_main_menu(menu); break;
	case credits_menu_state: present_credits(menu); break;
	}

	return want;
}

menu_wants_t present_main_menu(menu_t* menu) {
	menu_wants_t want = menu_wants_to_keep_going;

	item_placement_t placement = {100.f, 300.f, 0};
	float font_size = 20;
	float margin_y = 10;

	if(present_item(menu, &placement, "Start game")) {
		printf("Selected: 'Start game'\n");
		want = menu_wants_to_play;
	}

	if(present_item(menu, &placement, "Credits")) {
		printf("Selected: 'Credits'\n");
		menu->state = credits_menu_state;
	}

	if(present_item(menu, &placement, "Quit")) {
		printf("Selected: 'Quit'\n");
		want = menu_wants_to_quit;
	}

	// Return to the top when reaching the bottom
	menu->current_item_index %= placement.item_index;

	return want;
}

void present_credits(menu_t* menu) {
	DrawText("Programming", 50, 50, 20, LIGHTGRAY);
	DrawText("Jakob \"Jordgubben\" Eklund", 50, 100, 35, LIGHTGRAY);

	// Are we done here?
	const char* return_hint = "(Press 'space' or 'enter' to return to main menu)";
	DrawText(return_hint,
		GetScreenWidth() - (MeasureText(return_hint, 16) + 50), GetScreenHeight() - 50,
		16, DARKGRAY
		);
	if(menu->current_item_selected) {
		menu->state = main_menu_state;
	}
}

bool present_item(menu_t* menu, item_placement_t* placement, const char* label) {
	const float font_size = 20;
	const float margin_y = 10;

	bool current = menu->current_item_index == placement->item_index++;
	Color color = current ? LIGHTGRAY : DARKGRAY;
	DrawText(label, placement->offset_x, placement->offset_y, font_size, color);
	placement->offset_y += margin_y + font_size;
	return current && menu->current_item_selected;
}
