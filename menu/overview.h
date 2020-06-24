#ifndef MENU_OVERVIEW_H
#define MENU_OVERVIEW_H
#else
#warning "Header file included more than once."
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Types //
typedef struct menu_ menu_t;
#ifdef IN_MENU_S
typedef struct menu_ {

} menu_t;
#endif

// Model //
menu_t* init_menu();
void free_menu(menu_t*);

// View //
void present_menu(menu_t*);

// Controller //
void process_input(menu_t*);


#ifdef __cplusplus
} // extern "C"
#endif
