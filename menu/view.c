#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define IN_MENU_S
#include "overview.h"

void  present_menu(menu_t* menu) {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawText("Hello, Proxima Centauri B!", 150, 100, 20, LIGHTGRAY);
	DrawFPS(0,0);
	EndDrawing();
}

