#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

#define IN_MENU_S
#include "overview.h"


void  present_menu(menu_t* menu) {
	BeginDrawing();
	ClearBackground(BLACK);

	float offset_x = 100, offset_y = 300;
	float font_size = 20;
	float margin_y = 10;
	int item_index = 0;

	{
		bool current = menu->current_index == item_index++;
		Color color = current ? LIGHTGRAY : DARKGRAY;
		DrawText("Start game", offset_x, offset_y, font_size, color);
		offset_y += margin_y + font_size;
		if(current && menu->current_selected) {
			printf("Selected: 'Start game'\n");
		}
	}

	{
		bool current = menu->current_index == item_index++;
		Color color = current ? LIGHTGRAY : DARKGRAY;
		DrawText("Credits", offset_x, offset_y, font_size, color);
		offset_y += margin_y + font_size;
		if(current && menu->current_selected) {
			printf("Selected: 'Credits'\n");
		}
	}

	{
		bool current = menu->current_index == item_index++;
		Color color = current ? LIGHTGRAY : DARKGRAY;
		DrawText("Quit", offset_x, offset_y, font_size, color);
		offset_y += margin_y + font_size;
		if(current && menu->current_selected) {
			printf("Selected: 'Quit'\n");
		}
	}

	// Return to the top when reaching the bottom
	menu->current_index %= item_index;

	DrawFPS(0,0);
	EndDrawing();
}

