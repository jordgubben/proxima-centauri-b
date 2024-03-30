#ifndef MENU_OVERVIEW_H
#define MENU_OVERVIEW_H
#else
#warning "Header file included more than once."
#endif

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Types //
typedef struct menu_ menu_t;
#ifdef IN_MENU_S
typedef struct menu_ {
	enum {
		main_menu_state,
		credits_menu_state,
	} state;
	int current_item_index;
	bool current_item_selected;
} menu_t;
#endif

typedef enum menu_wants_t {
	menu_wants_to_keep_going,
	menu_wants_to_play,
	menu_wants_to_quit,
} menu_wants_t;

// Model //
menu_t* init_menu();
void free_menu(menu_t*);

// View //
menu_wants_t present_menu(menu_t*);

// Controller //
void process_input(menu_t*);


#ifdef __cplusplus
} // extern "C"
#endif
